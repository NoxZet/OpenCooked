#include "Graphics2D.hpp"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "Model.hpp"
#include "RenderObject.hpp"

#define DEFAULT_FIFO_SIZE (256*1024)
#define XSCALE 1.0938f
#define XSCALE_WIDE XSCALE * 3.0f / 4.0f
#define CIRCLE_FAN 16
#define CIRCLE_FAN_PART (M_PI * 1.0f / 8.0f)

namespace Graphics {

static GXRModeObj *rmode = nullptr;
static void *frameBuffer[2] = { NULL, NULL };

Graphics2D::Graphics2D(GameLogic::GameLogic &gameLogic) {
	// Register with GameLogic controller to receive new objects
	gameLogic.registerObjectSubscriber(*this);


	// init the vi.
	VIDEO_Init();

	rmode = VIDEO_GetPreferredMode(NULL);
	wide = CONF_GetAspectRatio() == 1;

	// allocate 2 framebuffers for double buffering
	frameBuffer[0] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
	frameBuffer[1] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

	console_init(frameBuffer[0],20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);

	VIDEO_Configure(rmode);
	VIDEO_SetNextFramebuffer(frameBuffer[fb]);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();

	// setup the fifo and then init the flipper
	void *gp_fifo = NULL;
	gp_fifo = memalign(32,DEFAULT_FIFO_SIZE);
	memset(gp_fifo,0,DEFAULT_FIFO_SIZE);

	GX_Init(gp_fifo,DEFAULT_FIFO_SIZE);

	// clears the bg to color and clears the z buffer
	GX_SetCopyClear(background, 0x00ffffff);

	// other gx setup
	GX_SetViewport(0,0,rmode->fbWidth,rmode->efbHeight,0,1);
	yscale = GX_GetYScaleFactor(rmode->efbHeight,rmode->xfbHeight);
	xfbHeight = GX_SetDispCopyYScale(yscale);
	GX_SetScissor(0,0,rmode->fbWidth,rmode->efbHeight);
	GX_SetDispCopySrc(0,0,rmode->fbWidth,rmode->efbHeight);
	GX_SetDispCopyDst(rmode->fbWidth,xfbHeight);
	GX_SetCopyFilter(rmode->aa,rmode->sample_pattern,GX_TRUE,rmode->vfilter);
	GX_SetFieldMode(rmode->field_rendering,((rmode->viHeight==2*rmode->xfbHeight)?GX_ENABLE:GX_DISABLE));

	GX_SetCullMode(GX_CULL_NONE);
	GX_CopyDisp(frameBuffer[fb],GX_TRUE);
	GX_SetDispCopyGamma(GX_GM_1_0);


	// Setup the vertex descriptor
	// Vertex direct data
	// Indexed color data
	GX_ClearVtxDesc();
	GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_CLR0, GX_INDEX8);

	// setup the vertex attribute table
	// describes the data
	// args: vat location 0-7, type of data, data format, size, scale
	// so for ex. in the first call we are sending position data with
	// 3 values X,Y,Z of size F32. scale sets the number of fractional
	// bits for non float data.
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8,	0);

	GX_SetNumChans(1);
	GX_SetNumTexGens(0);
	GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORDNULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);

	// setup our camera at the origin
	// looking down the -z axis with y up
	guVector cam = {0.0F, 0.0F, 0.0F},
			up = {0.0F, 1.0F, 0.0F},
			look = {0.0F, 0.0F, -1.0F};

	guLookAt(view, &cam, &up, &look);


	// setup our projection matrix
	// this creates a perspective matrix with a view angle of 90,
	// and aspect ratio based on the display resolution
	f32 w = rmode->viWidth;
	f32 h = rmode->viHeight;
	guPerspective(perspective, 45, (f32)w/h, 0.1F, 300.0F);
	GX_LoadProjectionMtx(perspective, GX_PERSPECTIVE);
	
	
	/*printf("\x1b[0;0H");
	printf("viTVMode: %d\nfbWidth: %d\nefbHeight: %d\nxfbHeight: %d\nviXOrigin: %d\nviYOrigin: %d\nviWidth: %d\nviHeight: %d\nAspect: %d\nCalculated w: %d",
		rmode->viTVMode, rmode->fbWidth, rmode->efbHeight, rmode->xfbHeight, rmode->viXOrigin, rmode->viYOrigin, rmode->viWidth, rmode->viHeight, CONF_GetAspectRatio(),
		(u16)((16.0f * (f32)rmode->xfbHeight) / 9.0f)
	);*/
	
	createCircle();

	auto circleObj = new RenderObject(circle);
	circleObj->setScale(20.0f, 20.0f, 20.0f);
	circleObj->setPosition(-30.0f, -10.0f, 0.0f);
	circleObj->setColor(0xff, 0x80, 0x00);
	objects.push_back(circleObj);
	
	circleObj = new RenderObject(circle);
	circleObj->setScale(20.0f, 20.0f, 20.0f);
	circleObj->setPosition(30.0f, -20.0f, 0.0f);
	circleObj->setColor(0xff, 0x00, 0x80);
	objects.push_back(circleObj);
	
	circleObj = new RenderObject(circle);
	circleObj->setScale(20.0f, 20.0f, 20.0f);
	circleObj->setPosition(30.0f, 30.0f, 0.0f);
	circleObj->setColor(0x00, 0xa0, 0xa0);
	objects.push_back(circleObj);
}

void Graphics2D::createCircle() {
	f32 r = 0.1f;
	void *dispList = memalign(32, 704);
	memset(dispList, 0, 704);
	DCInvalidateRange(dispList, 704);
	GX_BeginDispList(dispList, 704);
	GX_Begin(GX_TRIANGLES, GX_VTXFMT0, 3 * CIRCLE_FAN);
	
	// Draw circle as a fan
	f32 part = 0.0f;
	f32 part2;
	for (int i = 0; i < CIRCLE_FAN; i++) {
		// Calculate segment coords using trigonometry
		part2 = part + CIRCLE_FAN_PART;
		GX_Position3f32(sin(part) * r, cos(part) * r, 0.0f);
		GX_Color1x8(0);
		GX_Position3f32(0.0f, 0.0f, 0.0f);	// Center
		GX_Color1x8(0);
		GX_Position3f32(sin(part2) * r, cos(part2) * r, 0.0f);
		GX_Color1x8(0);
		part = part2;
	}
	
	GX_End();
	u32 dispSize = GX_EndDispList();
	circle = new Model(dispList, dispSize);
}

void Graphics2D::tick() {
	u32 *colorf = new u32(3);

	// do this before drawing
	GX_SetViewport(0,0,rmode->fbWidth,rmode->efbHeight,0,1);
	
	
	guMtxTransApply(view, currView, 0.0f, 0.0f, -126.0f);
	// Rescale because pixels aren't square
	guMtxScaleApply(currView, currView, wide ? XSCALE_WIDE: XSCALE, 1.0f, 1.0f);

	for (IRenderObject *object : objects) {
		object->draw(currView);
		//GX_DrawDone();
		GX_Flush();
	}

	// do this stuff after drawing
	GX_DrawDone();
	

	//fb ^= 1;		// flip framebuffer
	GX_SetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
	GX_SetColorUpdate(GX_TRUE);
	GX_CopyDisp(frameBuffer[fb],GX_TRUE);

	VIDEO_SetNextFramebuffer(frameBuffer[fb]);

	VIDEO_Flush();

	VIDEO_WaitVSync();
	
	delete[] colorf;
}

void Graphics2D::newObject(std::shared_ptr<Common::GameObject> commonPtr) {
	RenderObject *object = new RenderObject(commonPtr, circle);
	objects.push_back(object);
}
	
}
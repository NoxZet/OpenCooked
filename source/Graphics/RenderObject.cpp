#include "RenderObject.hpp"

namespace Graphics {

void RenderObject::draw(Mtx view) {
	Mtx model, modelview;
	// Calculate and load matrix for displaying
	guMtxIdentity(model);
	guMtxScaleApply(model, model, sx, sy, sz);
	guMtxTransApply(model, model, x / 5, -y / 5, -z / 5);
	guMtxConcat(view, model, modelview);
	
	// Set color indirect array to this RenderObject's color
	GX_SetArray(GX_VA_CLR0, &color, 4*sizeof(u8));
	
	this->model->draw(modelview);
}

}
#include "RenderObject.hpp"

namespace Graphics {

void RenderObject::draw(Mtx view) {
	setColor(commonObject->cr, commonObject->cg, commonObject->cb, 0xff);
	
	Mtx model, modelview;
	// Calculate and load matrix for displaying
	guMtxIdentity(model);
	guMtxScaleApply(model, model, commonObject->sx, commonObject->sy, commonObject->sz);
	guMtxTransApply(model, model, commonObject->x / 5, -commonObject->y / 5, -commonObject->z / 5);
	guMtxConcat(view, model, modelview);
	
	// Set color indirect array to this RenderObject's color
	GX_SetArray(GX_VA_CLR0, &color, 4*sizeof(u8));
	
	this->model->draw(modelview);
}

}
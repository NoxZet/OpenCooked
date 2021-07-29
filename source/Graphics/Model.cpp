#include "Model.hpp"

namespace Graphics {

void Model::draw(Mtx view) {
	// Load the modelview matrix into matrix memory
	GX_LoadPosMtxImm(view, GX_PNMTX0);
	
	// Render modelList
	GX_CallDispList(modelList, modelSize);
}

}
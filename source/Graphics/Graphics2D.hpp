#pragma once
#include <stdlib.h>
#include <string.h>
#include <gccore.h>
#include <vector>
#include "IModel.hpp"
#include "IRenderObject.hpp"

namespace Graphics {
	class Graphics2D {
		public:
			Graphics2D();
			void createCircle();
			void tick();
		private:
			IModel *circle;
			std::vector<IRenderObject*> objects;
			bool wide;
			
			u32	fb = 0;
			GXColor background = {0, 0, 0, 0xff};
			f32 yscale;
			u32 xfbHeight;
			Mtx view, currView;
			Mtx44 perspective;
	};
}
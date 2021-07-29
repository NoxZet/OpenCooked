#pragma once
#include <stdlib.h>
#include <string.h>
#include <gccore.h>

namespace Graphics {
	class IRenderObject {
		public:
			virtual void draw(Mtx view) = 0;
			virtual void setPosition(f32 x, f32 y, f32 z) = 0;
			virtual void setColor(u8 cr, u8 cg, u8 cb) = 0;
			virtual void setColor(u32 color) = 0;
			virtual void setAlpha(u8 ca) = 0;
			virtual void setScale(f32 sx, f32 sy, f32 sz) = 0;
	};
}
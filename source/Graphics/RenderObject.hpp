#pragma once
#include <stdlib.h>
#include <string.h>
#include <gccore.h>
#include <memory.h>
#include "IModel.hpp"
#include "IRenderObject.hpp"

namespace Graphics {
	class RenderObject: public IRenderObject {
		public:
			RenderObject(std::shared_ptr<Common::GameObject> commonPtr, IModel *model): commonObject(commonPtr), model(model) {};
			void draw(Mtx view) override;
			void setPosition(f32 x, f32 y, f32 z) override {
				this->x = x;
				this->y = y;
				this->z = z;
			}
			void setColor(u8 cr, u8 cg, u8 cb) override {
				color[0] = cr;
				color[1] = cg;
				color[2] = cb;
			}
			void setColor(u32 color) override {
				// Assign u32 value to an array of u8 by casting it to array of u32
				color = *((u32*)color);
			}
			void setAlpha(u8 ca) override {
				color[3] = ca;
			}
			void setScale(f32 sx, f32 sy, f32 sz) override {
				this->sx = sx;
				this->sy = sy;
				this->sz = sz;
			}
		private:
			f32 x, y, z;
			u8 color[4] = {0, 0, 0, 0xff};
			f32 sx, sy, sz;
			std::shared_ptr<Common::GameObject> commonObject;
			IModel *model;
	};
}
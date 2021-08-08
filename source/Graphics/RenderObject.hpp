#pragma once
#include <stdlib.h>
#include <string.h>
#include <gccore.h>
#include <memory>
#include "IModel.hpp"
#include "IRenderObject.hpp"
#include "../Common/GameObject.hpp"

namespace Graphics {
	class RenderObject: public IRenderObject {
		public:
			RenderObject(std::shared_ptr<Common::GameObject> commonPtr, IModel *model): commonObject(commonPtr), model(model) {};
			~RenderObject() override {};
			void draw(Mtx view) override;
			void setColor(u8 cr, u8 cg, u8 cb, u8 ca) {
				u8 *colorArr = (u8*)(&color);
				colorArr[0] = cr;
				colorArr[1] = cg;
				colorArr[2] = cb;
				colorArr[3] = ca;
			}
		private:
			u32 color;
			std::shared_ptr<Common::GameObject> commonObject;
			IModel *model;
	};
}
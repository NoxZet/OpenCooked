#pragma once
#include <stdlib.h>
#include <string.h>
#include <gccore.h>
#include "IModel.hpp"

namespace Graphics {
	class Model: public IModel {
		public:
			Model(void *modelList, u32 modelSize): modelList(modelList), modelSize(modelSize) {};
			void draw(Mtx view) override;
		private:
			void *modelList;
			u32 modelSize;
	};
}
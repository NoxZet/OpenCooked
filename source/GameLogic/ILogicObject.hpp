#pragma once
#include <stdlib.h>
#include <string.h>
#include <gccore.h>

namespace GameLogic {
	class ILogicObject {
		public:
			virtual ~ILogicObject() {};
			//virtual void setPosition(f32 x, f32 y, f32 z) = 0;
	};
}
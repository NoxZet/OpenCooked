#pragma once
#include <stdlib.h>
#include <string.h>
#include <gccore.h>

namespace GameLogic {
	class IGameObject {
		public:
			virtual ~IGameObject() {};
			//virtual void setPosition(f32 x, f32 y, f32 z) = 0;
	};
}
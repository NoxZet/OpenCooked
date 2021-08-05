#pragma once
#include <stdlib.h>
#include <string.h>
#include <gccore.h>
#include <memory>
#include "../Common/GameObject.hpp"

namespace GameLogic {
	class GameObject: public IGameObject {
		public:
			GameObject(std::shared_ptr<Common::GameObject> commonPtr) commonObject(commonPtr) {};
			//virtual void setPosition(f32 x, f32 y, f32 z) = 0;
		private:
			std::shared_ptr<Common::GameObject> commonObject;
	};
}
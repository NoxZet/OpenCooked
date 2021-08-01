#pragma once
#include <stdlib.h>
#include <string.h>
#include <gccore.h>
#include <memory>
#include "../Common/GameObject.hpp"

namespace Physics {
	class PhysicsObject {
		public:
			PhysicsObject(Common::GameObject *commonPtr) {
				commonObject = std::shared_ptr<Common::GameObject>(commonPtr);
			}
			//virtual void setPosition(f32 x, f32 y, f32 z) = 0;
		private:
			std::shared_ptr<Common::GameObject> commonObject;
	};
}
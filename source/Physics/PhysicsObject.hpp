#pragma once
#include <stdlib.h>
#include <string.h>
#include <gccore.h>
#include <memory>
#include "IPhysicsObject.hpp"
#include "../Common/GameObject.hpp"

namespace Physics {
	class PhysicsObject: public IPhysicsObject {
		public:
			PhysicsObject(std::shared_ptr<Common::GameObject> commonPtr): commonObject(commonPtr) {};
			~PhysicsObject() override {};
			bool isDeleted() override {
				return commonObject->deleted;
			}
			//void setPosition(f32 x, f32 y, f32 z) override;
		private:
			std::shared_ptr<Common::GameObject> commonObject;
	};
}
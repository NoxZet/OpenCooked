#pragma once
#include <stdlib.h>
#include <string.h>
#include <gccore.h>

namespace Physics {
	class IPhysicsObject {
		public:
			virtual ~IPhysicsObject() {};
			virtual bool isDeleted() = 0;
			//virtual void setPosition(f32 x, f32 y, f32 z) = 0;
	};
}
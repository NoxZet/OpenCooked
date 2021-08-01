#pragma once
#include <stdlib.h>
#include <string.h>
#include <gccore.h>
#include <vector>
#include "IPhysicsObject.hpp"

namespace Physics {
	class Physics {
		public:
			Physics();
			void tick();
		private:
			std::vector<IPhysicsObject*> objects;
	};
}
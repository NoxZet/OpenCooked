#pragma once
#include <stdlib.h>
#include <string.h>
#include <gccore.h>
#include <memory>
#include "GameObject.hpp"

namespace Common {
	class IObjectSubscriber {
		public:
			virtual void newObject(std::shared_ptr<Common::GameObject> commonPtr) = 0;
	};
}
#pragma once
#include <stdlib.h>
#include <string.h>
#include <gccore.h>
#include "GameObject.hpp"

namespace Common {
	class IObjectSubscriber {
		void newObject(GameObject *commonPtr) = 0;
	};
}
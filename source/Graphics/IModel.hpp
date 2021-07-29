#pragma once

#include <stdlib.h>
#include <string.h>
#include <gccore.h>

namespace Graphics {
	class IModel {
		public:
			virtual void draw(Mtx view) = 0;
	};
}
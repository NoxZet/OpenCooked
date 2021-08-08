#pragma once
#include <stdlib.h>
#include <string.h>
#include <gccore.h>

namespace Graphics {
	class IRenderObject {
		public:
			virtual ~IRenderObject() {};
			virtual bool isDeleted() = 0;
			virtual void draw(Mtx view) = 0;
	};
}
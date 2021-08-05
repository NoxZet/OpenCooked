#pragma once
#include <stdlib.h>
#include <string.h>
#include <gccore.h>

namespace Common {
	struct GameObject {
		f32 x, y, z;
		f32 dir;
		u32 id, type;
		f32 scale;
		bool exists = true;
	};
}
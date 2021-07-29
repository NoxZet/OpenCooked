#include <stdlib.h>
#include <string.h>
#include <gccore.h>

namespace Graphics {
	struct Vertex {
		f32 vx, vy, vz;
		f32 nx, ny, nz;
		u8 cr, cg, cb;
		f32 tx, ty;
	};
}
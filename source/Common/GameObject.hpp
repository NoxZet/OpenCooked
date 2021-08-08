#pragma once
#include <stdlib.h>
#include <string.h>
#include <gccore.h>

namespace Common {
	struct GameObject {
		// Coordinates of the object's bottom center
		f32 x, y, z;
		// Applied to models which have a color scheme (for example a colored shirt to identify player)
		// In WIP 2D graphics colors whole geometrical shape
		u8 cr, cg, cb;
		// Model scale - for 2D graphics:
		// sx = sy = circle radius
		// sx = rectangle width, sy = rectangle height
		f32 sx, sy, sz;
		// rot = direction and rotation around z axis - ccw, starting facing right
		f32 rot;
		// id should be unique through the whole program
		u32 id;
		// type from which model to be used can be devised
		u32 type;
		// If set to true, all controllers will deallocate their own object wrapping this GameObject
		// Only the main carrying object (GameLogic controller) should set this variable
		bool deleted = false;
	};
}
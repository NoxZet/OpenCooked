#pragma once
#include <stdlib.h>
#include <string.h>
#include <gccore.h>
#include <vector>
#include "IGameObject.hpp"

namespace GameLogic {
	class GameLogic {
		public:
			GameLogic();
			void tick();
		private:
			std::vector<IGameObject*> objects;
	};
}
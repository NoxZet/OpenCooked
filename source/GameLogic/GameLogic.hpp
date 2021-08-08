#pragma once
#include <stdlib.h>
#include <string.h>
#include <gccore.h>
#include <vector>
#include "IGameObject.hpp"
#include "../Common/IObjectSubscriber.hpp"

namespace GameLogic {
	class GameLogic {
		public:
			// GameLogic is created, then it's passed to other controllers, and only after
			// that game objects can be created (in init, not in constructor), as other controllers
			// would not receive them
			GameLogic();
			void init();
			void tick();
			void registerObjectSubscriber(Common::IObjectSubscriber &objectSubscriber);
		private:
			void createObject();
			// Deletes objects at the given index - undefined if `i < 0 || i >= objects.size()`
			void deleteObject(u32 i);
			std::vector<IGameObject*> objects;
			std::vector<Common::IObjectSubscriber*> objectSubscribers;
	};
}
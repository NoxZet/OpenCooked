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
			GameLogic();
			void tick();
			void registerObjectSubscriber(Common::IObjectSubscriber *objectSubscriber);
		private:
			std::vector<IGameObject*> objects;
			std::vector<Common::IObjectSubscriber*> objectSubscribers;
	};
}
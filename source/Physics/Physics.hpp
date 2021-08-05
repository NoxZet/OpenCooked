#pragma once
#include <stdlib.h>
#include <string.h>
#include <gccore.h>
#include <vector>
#include "IPhysicsObject.hpp"
#include "../Common/IObjectSubscriber.hpp"
#include "../GameLogic/GameLogic.hpp"

namespace Physics {
	class Physics: public Common::IObjectSubscriber {
		public:
			Physics(GameLogic::GameLogic *gameLogic);
			void tick();
			void newObject(std::shared_ptr<Common::GameObject> commonPtr) override;
		private:
			std::vector<IPhysicsObject*> objects;
	};
}
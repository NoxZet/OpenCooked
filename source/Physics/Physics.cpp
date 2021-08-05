#include "Physics.hpp"
#include "PhysicsObject.hpp"

namespace Physics {

Physics::Physics(GameLogic::GameLogic &gameLogic) {
	gameLogic.registerObjectSubscriber(*this);
}

void Physics::tick() {
	// stub
}

void Physics::newObject(std::shared_ptr<Common::GameObject> commonPtr) {
	PhysicsObject *object = new PhysicsObject(commonPtr);
	objects.push_back(object);
}

}
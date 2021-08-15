#include "Physics.hpp"
#include <algorithm>
#include "PhysicsObject.hpp"

namespace Physics {

Physics::Physics(GameLogic::GameLogic &gameLogic) {
	gameLogic.registerObjectSubscriber(*this);
}

Physics::~Physics() {
	for (auto object : objects) {
		delete object;
	}
}

void Physics::tick() {
	clearObjects();
	
	// stub
}

void Physics::clearObjects() {
	// We deallocate the IPhysicsObjects while moving all following objects back to fill in the gaps created
	u32 deleted = 0;
	for (u32 i = 0; i < objects.size(); i++) {
		objects[i - deleted] = objects[i];
		if (objects[i]->isDeleted()) {
			delete objects[i];
			deleted++;
		}
	}
	// Remove the elements at the end (if there's valid objects in them, they were moved back in the previous step)
	objects.erase(objects.end() - deleted, objects.end());
}

void Physics::newObject(std::shared_ptr<Common::GameObject> commonPtr) {
	PhysicsObject *object = new PhysicsObject(commonPtr);
	objects.push_back(object);
}

}
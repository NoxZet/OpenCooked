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
	// - See https://en.wikipedia.org/wiki/Erase–remove_idiom
	// - In a nutshell, remove_if moves all elements that match the predicate to the end of the
	//   vector and returns a pointer to the first of these elements, it keeps the vector's length
	auto deleteIt = std::remove_if(objects.begin(), objects.end(), [](IPhysicsObject *object) {
		return object->isDeleted();
	});
	// - Then we deallocate the RenderObjects
	for (auto deallocIt = deleteIt; deallocIt != objects.end(); deallocIt++) {
		delete *deallocIt;
	}
	// - Erase removes all elements past the input pointer
	objects.erase(deleteIt, objects.end());
}

void Physics::newObject(std::shared_ptr<Common::GameObject> commonPtr) {
	PhysicsObject *object = new PhysicsObject(commonPtr);
	objects.push_back(object);
}

}
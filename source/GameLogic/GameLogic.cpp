#include "GameLogic.hpp"
#include "GameObject.hpp"

namespace GameLogic {

GameLogic::GameLogic() {
	// stub
}

void GameLogic::tick() {
	// stub
}

void GameLogic::init() {
	// Example object creation
	createObject();
}

void GameLogic::registerObjectSubscriber(Common::IObjectSubscriber &objectSubscriber) {
	objectSubscribers.push_back(&objectSubscriber);
}

void GameLogic::createObject() {
	// Create and initialize the game object (both data store and logic object)
	std::shared_ptr<Common::GameObject> commonPtr = std::make_shared<Common::GameObject>();
	commonPtr->scale = 20;
	GameObject *gameObject = new GameObject(commonPtr);
	
	// Save object to GameLogic controller
	objects.push_back(gameObject);

	// Distribute object to other controllers
	for (auto subscriber : objectSubscribers) {
		subscriber->newObject(commonPtr);
	}
}

}
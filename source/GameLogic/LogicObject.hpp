#pragma once
#include <stdlib.h>
#include <string.h>
#include <gccore.h>
#include <memory>
#include "../Common/GameObject.hpp"

namespace GameLogic {
	class LogicObject: public ILogicObject {
		public:
			LogicObject(std::shared_ptr<Common::GameObject> commonPtr): commonObject(commonPtr) {};
			~LogicObject() override {
				// This is the main carrying wrapper object, if it's deleted, we want to
				// delete all other wrapper objects as well
				commonObject->deleted = true;
			};
			//virtual void setPosition(f32 x, f32 y, f32 z) = 0;
		private:
			std::shared_ptr<Common::GameObject> commonObject;
	};
}
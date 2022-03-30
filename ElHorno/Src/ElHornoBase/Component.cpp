#include "Component.h"
#include "CheckML.h"

namespace El_Horno {
	Component::~Component() {
		entity_ = nullptr;
	}

	void Component::setActive(bool a) {
		active_ = a;
		if (active_)
			onEnable();
		else
			onDisable();
	}
}
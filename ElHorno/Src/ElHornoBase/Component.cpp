#include "Component.h"
#include "CheckML.h"

namespace El_Horno {

	Component::~Component() {
		entity_ = nullptr;
	}

	// activa o desactiva el componente
	void Component::setActive(bool a) {
		active_ = a;
		if (active_)
			onEnable();
		else
			onDisable();
	}
}
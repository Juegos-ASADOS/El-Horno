#include "Component.h"
#include "CheckMl.h"

Component::~Component(){
	entity_ = nullptr;
}

void Component::setActive(bool a) {
	active_ = a;
	if (active_)
		onEnable();
	else
		onDisable();
}
#pragma once
#include "../json.hpp"

using json = nlohmann::json;
class Component;

class Factory
{

public:
	Factory() {};

	virtual Component* createComponent(json& args) = 0;

};


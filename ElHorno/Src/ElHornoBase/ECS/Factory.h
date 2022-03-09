#pragma once
#include "../json.hpp"

class Component;

class Factory
{
public:
	Factory() {};

	virtual Component* createComponent(nlohmann::json& args) = 0;
};

class TransformFactory : public Factory {
public:
	virtual Component* createComponent(nlohmann::json& args) override;
};
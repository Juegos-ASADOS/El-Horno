#pragma once
#ifndef _FACTORY_H
#define _FACTORY_H

#include "json.hpp"

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

class MeshFactory : public Factory {
public:
	virtual Component* createComponent(nlohmann::json& args) override;
};

class CameraFactory : public Factory {
public:
	virtual Component* createComponent(nlohmann::json& args) override;
};

#endif _FACTORY_H
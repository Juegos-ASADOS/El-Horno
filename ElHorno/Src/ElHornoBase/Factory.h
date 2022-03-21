#pragma once
#ifndef _FACTORY_H
#define _FACTORY_H

class Component;

class Factory
{
public:
	Factory() {};

	/*template<typename ...Ts>
	Component* createComponent(Ts &&...args) {};*/
};

//class TransformFactory : public Factory {
//public:
//	template<typename ...Ts>
//	Component* createComponent(Ts &&...args);
//};
//
//class MeshFactory : public Factory {
//public:
//	template<typename ...Ts>
//	Component* createComponent(Ts &&...args);
//};
//
//class CameraFactory : public Factory {
//public:
//	template<typename ...Ts>
//	Component* createComponent(Ts &&...args);
//};

#endif _FACTORY_H
#pragma once
#ifndef _FACTORY_H
#define _FACTORY_H

class Component;

class Factory
{
public:
	Factory() {};

	template<typename T, typename ...Ts>
	static T* createComponent(Ts &&...args) { return new T(args...); };
};

//class TransformFactory : public Factory {
//public:
//	template<typename ...Ts>
//	Component* createComponent(Ts &&...args)
//	{
//		return new Transform(args);
//	}
//};
//
//class MeshFactory : public Factory {
//public:
//	template<typename ...Ts>
//	Component* createComponent(Ts &&...args) 
//	{
//		return new Mesh(args);
//	}
//};
//
//class CameraFactory : public Factory {
//public:
//	template<typename ...Ts>
//	Component* createComponent(Ts &&...args)
//	{
//		return new CameraComponent(args);
//	}
//};

#endif _FACTORY_H
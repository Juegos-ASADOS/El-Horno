//#pragma once
//#ifndef _AudioComponent_H
//#define _AudioComponent_H
//
//#include <string>
//#include "json.hpp"
//#include "Component.h"
//
//namespace Ogre {
//	/*class AxisAlignedBox;
//	class Entity;
//	class Mesh;*/
//	//class Camera;
//	class Vector3;
//}
//
//class AudioComponent : public Component
//{
//public:
//
//	AudioComponent(nlohmann::json& args);
//	~AudioComponent();
//
//	//void start() override;
//	void update()override;
//
//	void onEnable() override {};
//	void onDisable()override {};
//
//	virtual void playSound(std::string path);
//
//private:
//	Ogre::Vector3 pos_;
//	Ogre::Vector3 vel_;
//
//	int nChannel;
//	std::string audioRoute;
//};
//
//#endif _AudioComponent_H
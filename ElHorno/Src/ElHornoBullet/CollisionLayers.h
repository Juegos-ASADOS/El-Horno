#pragma once
#ifndef _COLLISION_LAYERS_H
#define _COLLISION_LAYERS_H

#include <string>
#include <unordered_map>

namespace El_Horno {
	//Almacena las capas de colisión definidas por el usuario
	class _declspec(dllexport) CollisionLayers
	{
	public:
		CollisionLayers();
		~CollisionLayers();
		
		bool addLayer(const std::string& name);
		
		int getLayer(const std::string& name) const;
	
	private:
		int layerCount_;
		std::unordered_map<std::string, int> layers;
	};
}


#endif _COLLISION_LAYERS_H
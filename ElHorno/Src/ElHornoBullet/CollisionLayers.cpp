#include "CollisionLayers.h"
//#include "CheckML.h"

//Significado:
//1 << 0 = `0000 0001`
//1 << 1 = `0000 0010`
//1 << 2 = `0000 0100`
#define BIT(x) (1<<(x))

namespace El_Horno {
	CollisionLayers::CollisionLayers()
	{
		//Capa inicial
		layerCount_ = 1;
	}
	CollisionLayers::~CollisionLayers()
	{

	}
	bool CollisionLayers::addLayer(const std::string& name)
	{
		//Comprueba que no exista ya la layer
		if (layers.find(name) != layers.end())
			return false;

		//Y la inserta con el BIT especifico de la layerCount actual
		layers.insert({ name, BIT(layerCount_++) });
		return true;
	}
	int CollisionLayers::getLayer(const std::string& name) const
	{
		//Devuelve el valor tras haber aplicado BIT
		auto layer = layers.find(name);
		if (layer == layers.end())
			return -1;
		return layer->second;
	}
}
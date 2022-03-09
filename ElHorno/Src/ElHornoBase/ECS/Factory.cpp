#include "Factory.h"
#include "../Components/Transform.h"
#include "../Components/Mesh.h"

Component* TransformFactory::createComponent(nlohmann::json& args)
{
	return new Transform(args);
}

Component* MeshFactory::createComponent(nlohmann::json& args)
{
    return new Mesh(args);
}

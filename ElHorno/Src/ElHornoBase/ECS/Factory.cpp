#include "Factory.h"
#include "../Components/Transform.h"
#include "../Components/Mesh.h"
#include "../Components/CameraComponent.h"

Component* TransformFactory::createComponent(nlohmann::json& args)
{
	return new Transform(args);
}

Component* MeshFactory::createComponent(nlohmann::json& args)
{
    return new Mesh(args);
}

Component* CameraFactory::createComponent(nlohmann::json& args)
{
	return new CameraComponent(args);
}

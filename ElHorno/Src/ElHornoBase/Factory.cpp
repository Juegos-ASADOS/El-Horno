#include "Factory.h"
#include "Transform.h"
#include "Mesh.h"
#include "CameraComponent.h"

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

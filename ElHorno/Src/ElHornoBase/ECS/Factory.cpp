#include "Factory.h"
#include "../Components/Mesh.h"

Component* MeshFactory::createComponent(nlohmann::json& args)
{
    return new Mesh(args);
}

#include "Factory.h"
#include "../Components/Transform.h"

Component* TransformFactory::createComponent(nlohmann::json& args)
{
	return new Transform(args);
}

#include "ElHornoBase.h"; 
#include "SinbadAnimTest.h"
#include "InputManager.h"
#include "AnimatorController.h"

#include "Transform.h"
#include "Entity.h"
#include "HornoConversions.h"
#include <OgreAnimationState.h>
#include <OgreEntity.h>
#include "CheckMl.h"

namespace El_Horno
{

SinbadAnimTest::SinbadAnimTest()
{
	
}

SinbadAnimTest::~SinbadAnimTest()
{

}

void SinbadAnimTest::start()
{
	// Obtenemos los componentes y entidades necesarios
	tr_ = entity_->getComponent<Transform>("transform");
	node_ = tr_->getNode();

	anim_ = entity_->getComponent<AnimatorController>("animatorController");


}

void SinbadAnimTest::update()
{
	if (ElHornoBase::getInstance()->getInputManager()->IsKeyDown(SDL_Scancode::SDL_SCANCODE_SPACE))
	{
		if (!dancing)
		{
			anim_->setAnimBool("AnyState", "Dance", true);
			dancing = true;
		}
	}

	if (ElHornoBase::getInstance()->getInputManager()->IsKeyDown(SDL_Scancode::SDL_SCANCODE_W))
	{
		if (!walking)
		{
			anim_->setAnimBool("IdleBase", "RunBase", true);
			walking = true;
		}
	}
	else 

	{
		if (walking)
		{
			anim_->setAnimBool("RunBase", "IdleBase", true);
			walking = false;
		}
	}
}
}




//TODO REVISAR SI PONER "" O <>
#include "GameFactories.h"
#include "Entity.h"
#include "ElHornoBase.h"
#include "PlayerInteract.h"
#include "Event.h"
#include "InputManager.h"
#include <EntityId.h>
#include <Transform.h>
#include <Scene.h>
#include <Mesh.h>
#include <Rigibody.h>

El_Horno::PlayerInteract::PlayerInteract() : sizeCart(0), capacity(empty)
{
}

void El_Horno::PlayerInteract::start()
{
	//Cogemos el input manager
	input = ElHornoBase::getInstance()->getInputManager();
}

void El_Horno::PlayerInteract::update()
{

}

bool El_Horno::PlayerInteract::recieveEvent(Event* ev)
{
	//Comprobamos colisiones
	if (ev->ty_ == EventType::CollisionStay) {
		return processCollisionStay(ev);
	}
	return false;
}

bool El_Horno::PlayerInteract::processCollisionStay(Event* ev)
{
	// Coge Id de la entidad
	Entity* entity = static_cast<rbTriggerStay*>(ev)->other_->getParent();

	if (entity == nullptr)
		return false;

	EntityId* idEntity = entity->getComponent<EntityId>("entityid");

	//TODO SI TIENE ALGUN OBJETO EN LA MANO...

	if (idEntity != nullptr) {

		//Y es el carrito de la compra...
		if (idEntity->isCart()) {
			manageCart();
			return true;
		}
		//Si es la estanteria...
		else if (idEntity->isEstantery()) {
			return manageEstantery(entity, idEntity);
		}
	}
	return false;
}

void El_Horno::PlayerInteract::manageCart()
{

	//Si pulsas la tecla E...
	if (input->isKeyDown(SDL_SCANCODE_E)) {

		//TODO ELIMINAMOS EL OBJETO QUE TENGA EN LA MANO

		//TODO COMPROBAR SI EL OBJETO QUE QUIERO METER SE PUEDE METER O LO TIRO AL SUELO
		//Mientras no esté hecho siempre se añade y ale
		sizeCart++;

		//TODO SWITCH
		switch (sizeCart)
		{
		case 10:
			capacity = full;
			//PROGRAMAR EL CAMBIO DE CARRITO
			break;
		case 7:
			capacity = half_Full;
			//PROGRAMAR EL CAMBIO DE CARRITO
			break;
		case 3:
			capacity = half_Empty;
			//PROGRAMAR EL CAMBIO DE CARRITO
			break;
		case 0:
			capacity = empty;
			//PROGRAMAR EL CAMBIO DE CARRITO
			break;
		default:
			break;
		}

		//Meter algun return false en la comprobacion en caso de que no se pueda meter supongo
		//O igual no pq tb ocurre un evento de tirar el objeto al suelo no c no soi 100tifiko
	}
	//TODO SI PULSAS OTRA TECLA COGES O SUELTAS EL CARRITO

}

bool El_Horno::PlayerInteract::manageEstantery(Entity* entity, EntityId* idEntity)
{

	//Si no tiene alimentos que coger...
	if (entity_->getChildCount() != 0)
		//No ocurre nada
		return false;

	// TODO Mostrar tecla E en la UI 

	if (input->isKeyDown(SDL_SCANCODE_E)) {

		Scene* scene = entity->getScene();
		Transform* playerTr = entity_->getComponent<Transform>("transform");

		// Crear entidad producto
		Entity* product = scene->addEntity("product", scene->getName(), entity_);

		/*product->addComponent<Transform>("transform", HornoVector3(playerTr->getHornoPosition().x_ + 4, playerTr->getHornoPosition().y_, playerTr->getHornoPosition().z_),
			HornoVector3(0, 0, 0), HornoVector3(0.25, 0.25, 0.25));*/
		product->addComponent<Transform>("transform", HornoVector3(-10, 10, 0),
			HornoVector3(-90, 0, 0), HornoVector3(25, 25, 25));

		product->addComponent<Mesh>("mesh", idEntity->getId());
		product->addComponent<RigidBody>("rigidbody", 2.0f, true, true, 0);
		product->addComponent<EntityId>("entityid", idEntity->getId());

		product->start();

		return true;
	}
}

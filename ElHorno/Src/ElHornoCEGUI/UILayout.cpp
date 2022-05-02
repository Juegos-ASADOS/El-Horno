#include "UILayout.h"
#include "UIManager.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/EventArgs.h>
#include "CheckML.h"
#include <iostream>

//El UIPushButton se crea un boton
//Se lo guarda
//Y le dice al root del UIManager que ahora es hijo de la ventana principal
namespace El_Horno {
	UILayout::UILayout(std::string layoutName, std::string name)
	{
		changeLayout(layoutName, name);
	}
	
	void UILayout::start()
	{
		uiManager = UIManager::getInstance();
	}
	
	UILayout::~UILayout()
	{
		removeLayout();
	}
	
	void UILayout::setParameters(std::vector<std::pair<std::string, std::string>> parameters)
	{
	}

	void UILayout::loadScheme(std::string schemeName)
	{
		uiManager->defineScheme(schemeName);
	}

	void UILayout::loadLayout()
	{
		layoutRoot = uiManager->loadLayout(layoutName_);
	}

	void UILayout::removeLayout()
	{
		if (layoutRoot == nullptr) return;

		layoutRoot->destroy();

		layoutRoot = nullptr;
	}
	// For example, if this window has a child attached to it named "Panel" 
	// which has its own children attached named "Okay" and "Cancel", 
	// you can access the window "Okay" from this window by using 
	// the name path "Panel/Okay".
	// To access "Panel", you would simply pass the name "Panel".

	void UILayout::subscribeChildEvent(std::string childName, bool (*func)(const CEGUI::EventArgs&))
	{
		if (layoutRoot == nullptr) return;

		if (!layoutRoot->getChild(childName)->isEventPresent(CEGUI::Window::EventMouseClick)){
			std::cout << "Carga del evento\n";
			layoutRoot->getChild(childName)->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(func));
		}
	}

	void UILayout::changeLayout(std::string layoutName, std::string name)
	{
		layoutName_ = layoutName;
		name_ = name;
	}


}
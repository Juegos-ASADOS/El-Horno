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
	UILayout::UILayout()
	{
	}

	UILayout::~UILayout()
	{
		removeLayouts();
	}

	void UILayout::start()
	{
		uiManager = UIManager::getInstance();
	}

	void UILayout::setLayoutVisibility(std::string layoutName, bool visible)
	{
		CEGUI::Window* wnd = getLayout(layoutName);
		if (wnd != nullptr) {
			wnd->setVisible(visible);
			if (visible) wnd->activate();
		}
	}

	//void UILayout::setLayoutVisibility(int layout, bool visible)
	//{
	//	CEGUI::Window* wnd = getLayout(layout);
	//	if (wnd != nullptr) {
	//		wnd->setVisible(visible);
	//		if (visible) wnd->activate();
	//	}
	//	else {
	//		std::cout << "Layout not found!\n";
	//	}
	//}

	//Añade un layout al vector y al root, y lo deja invisible
	//Nombre del layout, y nombre interno cualquiera(que no se repita)
	void UILayout::addLayout(std::string layoutName, std::string name)
	{
		if (getLayout(layoutName) != nullptr) {
			return;
		}

		CEGUI::Window* wnd = uiManager->createLayout(layoutName, name);
		wnd->setVisible(false);
		uiManager->getRoot()->addChild(wnd);
		layouts[layoutName] = wnd;
	}

	//Borra un layout del vector y del root
	void UILayout::removeLayout(std::string layoutName)
	{
		CEGUI::Window* wnd = getLayout(layoutName);
		if (wnd != nullptr) {
			auto it = layouts.find(layoutName);
			uiManager->getRoot()->removeChild(wnd);
			layouts.erase(it);
		}
	}

	//void UILayout::removeLayout(int layout)
	//{
	//	CEGUI::Window* wnd = getLayout(layout);
	//	if (wnd != nullptr) {
	//		uiManager->getRoot()->removeChild(wnd);
	//		layouts.erase(layouts.begin() + layout);
	//	}
	//	else {
	//		std::cout << "Couldnt remove layout. Layout not found!\n";
	//	}
	//}
	
	void UILayout::setParameters(std::vector<std::pair<std::string, std::string>> parameters)
	{
	}

	void UILayout::loadScheme(std::string schemeName)
	{
		uiManager->defineScheme(schemeName);
	}


	void UILayout::setScale(std::string layoutName, float x, float y)
	{
		CEGUI::Window* wnd = getLayout(layoutName);
		if (wnd != nullptr) {
			wnd->setSize(CEGUI::USize(CEGUI::UDim(x, 0), CEGUI::UDim(y, 0)));
		}
	}
	
	//void UILayout::setScale(int layout, float x, float y)
	//{
	//	CEGUI::Window* wnd = getLayout(layout);
	//	if (wnd != nullptr) {
	//		wnd->setSize(CEGUI::USize(CEGUI::UDim(x, 0), CEGUI::UDim(y, 0)));
	//	}
	//	else {
	//		std::cout << "Couldnt subscribe event. Layout not found!\n";
	//	}
	//}

	// For example, if this window has a child attached to it named "Panel" 
	// which has its own children attached named "Okay" and "Cancel", 
	// you can access the window "Okay" from this window by using 
	// the name path "Panel/Okay".
	// To access "Panel", you would simply pass the name "Panel".
	// ---------
	// --------- 
	// Subscribe una funcion a un widget de CEGUI. 
	// De momento SÓLO FUNCIONA CON PUSHBUTTON
	template<class T>
	void UILayout::subscribeChildEvent(std::string layoutName, std::string childName, void (T::* func)(), T* comp)
	{
		CEGUI::Window* wnd = getLayout(layoutName);
		if (wnd != nullptr) {
			wnd->getChild(childName)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(func, comp));
		}
	}	
	
	void UILayout::subscribeChildEvent(std::string layoutName, std::string childName, bool(*func)())
	{
		CEGUI::Window* wnd = getLayout(layoutName);
		if (wnd != nullptr) {
			wnd->getChild(childName)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(func));
		}
	}

	void UILayout::subscribeChildEvent(std::string layoutName, std::string childName, bool(*func)(const CEGUI::EventArgs& e))
	{
		CEGUI::Window* wnd = getLayout(layoutName);
		if (wnd != nullptr) {
			wnd->getChild(childName)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(func));
		}
	}

	void UILayout::subscribeChildEvent(std::string layoutName, std::string childName, std::function<bool(const CEGUI::EventArgs&)> func)
	{

		CEGUI::Window* wnd = getLayout(layoutName);
		if (wnd != nullptr) {
			wnd->getChild(childName)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(func));
		}
	}

	void UILayout::removeLayouts()
	{
		auto it = layouts.begin();
		while(it != layouts.end()){
			//CEGUI::WindowManager::getSingleton().de
			(*it).second->destroy();
			it++;
		}
		layouts.clear();
	}
	
	CEGUI::Window* UILayout::getLayout(std::string layoutName)
	{
		auto it = layouts.find(layoutName);

		if (it != layouts.end())
			return (*it).second;

		return nullptr;
	}

	void UILayout::addImageFile(const std::string& imageName, const std::string& imageFile)
	{
		if (!CEGUI::ImageManager::getSingleton().isDefined(imageFile)) {
			CEGUI::ImageManager::getSingleton().addFromImageFile(imageName, imageFile);
		}
	}

	void UILayout::addWidgetToLayout(const std::string& layoutName, const std::string& childName, const std::string& widgetType)
	{
		CEGUI::Window* wnd = getLayout(layoutName);
		if (wnd == nullptr) {
			//std::cout << "Couldnt add Widget. Layout not found!\n";
			return;
		}

		CEGUI::Window* child = uiManager->getWinMngr()->createWindow(widgetType, childName);
		wnd->addChild(child);
	}

	void UILayout::removeWidgetFromLayout(const std::string& layoutName, const std::string& childPath)
	{
		CEGUI::Window* wnd = getLayout(layoutName);
		if (wnd == nullptr) {
			//std::cout << "Couldnt remove Widget. Layout not found!\n";
			return;
		}

		wnd->destroyChild(childPath);
	}

	void UILayout::setChildProperty(const std::string& layoutName, const std::string& childPath, const std::string& propertyName, const std::string& values)
	{
		CEGUI::Window* wnd = getLayout(layoutName);
		if (wnd == nullptr) {
			//std::cout << "Couldnt remove Widget. Layout not found!\n";
			return;
		}

		//wdt->setProperty("SomeProperty", "True");
		wnd->getChild(childPath)->setProperty(propertyName, values);
	}

	//CEGUI::Window* UILayout::getLayout(int layout)
	//{
	//	if (layout >= 0 && layout < layouts.size()) {
	//		return layouts[layout];
	//	}
	//	return nullptr;
	//}

	//void UILayout::createButton(const std::string& scheme, const std::string& type, const std::string& name)
	//{
	//	CEGUI::PushButton* button = static_cast<CEGUI::PushButton*>(uiManager->createWidget(scheme + "/" + type, name));
	//	button->setText("PATATA");
	//	button->setUsingAutoRenderingSurface(true);
	//	button->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&UILayout::onClick, this));
	//}

	/*bool UILayout::onClick(const CEGUI::EventArgs& e)
	{
		std::cout << "POR FAVOR\n";
		return false;
	}*/


}
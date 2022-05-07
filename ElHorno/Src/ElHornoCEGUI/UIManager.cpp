#include "UIManager.h"

#include <GraphicsManager.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/Window.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include <InputManager.h>
#include <OgreRenderWindow.h>
#include "CheckML.h"
#include <iostream>

namespace El_Horno {
	UIManager* UIManager::instance_ = 0;

	UIManager::UIManager()
	{
		//CEGUI::OgreRenderer& auxiliar = CEGUI::OgreRenderer::bootstrapSystem(*renderWindow);
		//renderer = &auxiliar;

		//setUpResources();

		//createRoot();
	}

	UIManager::~UIManager()
	{
		//CEGUI::System::getSingleton().destroyGUIContext(*guiContext);
		//CEGUI::System::getSingleton().destroy();
		//CEGUI::OgreRenderer::destroy(*renderer);
		winMngr->destroyAllWindows();
		renderer->destroySystem();
	}

	UIManager* UIManager::getInstance()
	{
		return instance_;
	}


	bool UIManager::setupInstance()
	{
		if (instance_ == 0)
		{
			instance_ = new UIManager();
			return true;
		}

		return false;
	}

	void UIManager::setUpResources()
	{
		/*CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(
			CEGUI::System::getSingleton().getResourceProvider());
		rp->setResourceGroupDirectory("imagesets", "./mygame/datafiles/gui/imagesets/");*/


		//ImageManager,Font,Scheme,WidgetLookManager...
		CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
		CEGUI::Font::setDefaultResourceGroup("Fonts");
		CEGUI::Scheme::setDefaultResourceGroup("Schemes");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
		CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

		//CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
		//CEGUI::SchemeManager::getSingleton().createFromFile("Generic.scheme");
		////esto es la carga de recursos sobre como s eva a utilizar cegui (fuente de letra, letreros, puntero del raton etc etc)
		//CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

	}

	void UIManager::erase()
	{
		delete instance_;
	}

	void UIManager::createRoot()
	{
		if (root != nullptr)
			root->destroy();

		root = nullptr;

		//Ventana por defecto a modo de GameObject
		//Todos los botones texto etc se crean dentro de esta misma ventana
		root = winMngr->createWindow("DefaultWindow", "Root");
		
		root->setUsingAutoRenderingSurface(true);

		guiContext->setRootWindow(root);

		root->activate();
	}

	void UIManager::createContext()
	{
		//Seleccionamos el RenderTarget que usamos de ogre que usamos de Root de Renderizado
		renderer = &CEGUI::OgreRenderer::bootstrapSystem(*GraphicsManager::getInstance()->getRenderWindow());

		guiContext = &CEGUI::System::getSingleton().createGUIContext(renderer->getDefaultRenderTarget());

		winMngr = CEGUI::WindowManager::getSingletonPtr();

		//esto para que no se haga en la constructora
		setUpResources();

		createRoot();

		/*defineScheme("Generic");
		defineScheme("TaharezLook");

		root->addChild(winMngr->loadLayoutFromFile("TaharezLookOverview.layout"));*/
	}

	void UIManager::deleteContext()
	{
		//Eliminamos todas las ventanas, destruimos el GUIContext y el render de ogre
		removeLayoutRoot();
		CEGUI::System::getSingleton().destroyGUIContext(*guiContext);
		renderer->destroySystem();
	}

	void UIManager::defineScheme(std::string schemeName)
	{
		if (!CEGUI::SchemeManager::getSingleton().isDefined(schemeName + ".scheme")) {
			CEGUI::SchemeManager::getSingleton().createFromFile(schemeName + ".scheme"); 
		}
	}

	void UIManager::removeLayoutRoot()
	{
		if (root != nullptr)
			root->destroy();

		root = nullptr;
		
		createRoot();
	}

	CEGUI::Window* UIManager::loadLayout(std::string layoutName, std::string name)
	{
		//removeLayout();

		CEGUI::Window* window = createLayout(layoutName + ".layout", name);
		//setRootLayout(window);

		return window;
	}

	CEGUI::Window* UIManager::createLayout(std::string layoutName, std::string name)
	{
		CEGUI::Window* window = nullptr;
		if(name != "")
			window = winMngr->loadLayoutFromFile(layoutName + ".layout", name);
		else
			window = winMngr->loadLayoutFromFile(layoutName + ".layout");
		
		return window;
	}

	void UIManager::setRootLayout(CEGUI::Window* nRoot)
	{
		guiContext->setRootWindow(nRoot);

		root = nRoot;
	}

	void UIManager::changeScreenSize(int width, int height)
	{
		renderer->setDisplaySize(CEGUI::Size<float>(width, height));
		CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Size<float>(width, height));
	}

	void UIManager::update()
	{
		guiContext->draw();
		// draw GUI
		//CEGUI::System::getSingleton().renderAllGUIContexts();


		//root->render();
		//root->setRenderingSurface();
		//tendra que recorrer todos sus layouts

		/*auto iter = layouts.begin();
		while (iter != layouts.end()) {
			if ((*iter)->isActive()) {
				(*iter)->render();
			}
			iter++;
		}*/

	}

	void UIManager::changeText(CEGUI::Window* window, std::string text)
	{
		window->setText(text);
	}

	//Para cambiar la imagen del rat�n
	void UIManager::setMouseCursor(const std::string& imageFile)
	{
		guiContext->getMouseCursor().setDefaultImage(imageFile);
	}

	void UIManager::showMouseCursor()
	{
		InputManager::getInstance()->hideMouse();
		guiContext->getMouseCursor().show();
	}

	void UIManager::hideMouseCursor()
	{
		guiContext->getMouseCursor().hide();
	}

	void UIManager::setFont(const std::string& font)
	{
		CEGUI::FontManager::getSingleton().createFromFile(font + ".font");
		guiContext->setDefaultFont(font);
	}

	CEGUI::Window* UIManager::createWidget(const std::string& type, const std::string& name)
	{
		CEGUI::Window* wnd = winMngr->createWindow(type, name);
		root->addChild(wnd);
		wnd->activate();
		return wnd;
	}

	void UIManager::setWidgetDestRect(CEGUI::Window* wnd, const CEGUI::UDim& pos, const CEGUI::UDim& relativePos, const CEGUI::UDim& size, const CEGUI::UDim& relativeSize)
	{
		wnd->setPosition(CEGUI::UVector2(pos, relativePos));
		wnd->setSize(CEGUI::USize(size, relativeSize));
	}


	CEGUI::Window* UIManager::getRoot()
	{
		return root;
	}

	CEGUI::Window* UIManager::getWindow(const std::string& name)
	{
		//Si no fuciona intentar static_Cast
		return root->getChild(name);
	}

	CEGUI::WindowManager* UIManager::getWinMngr()
	{
		return winMngr;
	}


	void UIManager::changeAlpha(const std::string& imagePath, float alpha)
	{
		//Si sale error hacer static_cast
		CEGUI::Window* thumbnail = root->getChild(imagePath);
		thumbnail->setAlpha(alpha);
	}

	float UIManager::getAlpha(const std::string& namePath)
	{
		//Si sale error hacer static_cast
		CEGUI::Window* thumbnail = root->getChild(namePath);
		return thumbnail->getAlpha();
	}

	void UIManager::subscribeLayoutChildEvent(std::string layoutName, std::string childName, std::function<bool(const CEGUI::EventArgs&)> func)
	{
		CEGUI::Window* wnd = getLayout(layoutName);
		if (wnd != nullptr) {
			wnd->getChild(childName)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(func));
		}
	}

	void UIManager::subscribeChildEvent( std::string childName, std::function<bool(const CEGUI::EventArgs&)> func)
	{
		//you better know what you doing!
		root->getChild(childName)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(func));
	}

	void UIManager::addImageFile(const std::string& imageName, const std::string& imageFile)
	{
		if (!CEGUI::ImageManager::getSingleton().isDefined(imageFile)) {
			CEGUI::ImageManager::getSingleton().addFromImageFile(imageName, imageFile);
		}
	}

	void UIManager::addWidgetToLayout(const std::string& layoutName, const std::string& childName, const std::string& widgetType)
	{
		CEGUI::Window* wnd = getLayout(layoutName);
		if (wnd == nullptr) {
			return;
		}

		CEGUI::Window* child = winMngr->createWindow(widgetType, childName);
		wnd->addChild(child);
	}

	void UIManager::removeWidgetFromLayout(const std::string& layoutName, const std::string& childPath)
	{
		CEGUI::Window* wnd = getLayout(layoutName);
		if (wnd == nullptr) {
			return;
		}

		wnd->destroyChild(childPath);
	}

	void UIManager::setChildProperty(const std::string& layoutName, const std::string& childPath, const std::string& propertyName, const std::string& values)
	{
		CEGUI::Window* wnd = getLayout(layoutName);
		if (wnd == nullptr) {
			return;
		}

		//wdt->setProperty("SomeProperty", "True");
		wnd->getChild(childPath)->setProperty(propertyName, values);
	}


	void UIManager::setLayoutVisibility(std::string layoutName, bool visible)
	{
		CEGUI::Window* wnd = getLayout(layoutName);
		if (wnd != nullptr) {
			wnd->setVisible(visible);
			if (visible) wnd->activate();
		}
	}

	void UIManager::subscribeLayoutChildVisibility(std::string layoutName, std::string childName, bool visible)
	{
		CEGUI::Window* wnd = getLayout(layoutName);
		if (wnd != nullptr) {
			//wdt->setProperty("SomeProperty", "True");
			wnd->getChild(childName)->setVisible(visible);
			if (visible) wnd->getChild(childName)->activate();

		}
	}

	void UIManager::addLayout(std::string layoutName, std::string name)
	{
		if (getLayout(layoutName) != nullptr) {
			return;
		}

		CEGUI::Window* wnd = createLayout(layoutName, name);
		wnd->setVisible(false);
		root->addChild(wnd);
		layouts[layoutName] = wnd;
	}

	void UIManager::removeLayout(std::string layoutName)
	{
		CEGUI::Window* wnd = getLayout(layoutName);
		if (wnd != nullptr) {
			auto it = layouts.find(layoutName);
			root->removeChild(wnd);
			layouts.erase(it);
		}
	}

	void UIManager::removeLayouts()
	{
		auto it = layouts.begin();
		while (it != layouts.end()) {
			//CEGUI::WindowManager::getSingleton().de
			(*it).second->destroy();
			it++;
		}
		layouts.clear();
	}


	void UIManager::setLayoutScale(std::string layoutName, float x, float y)
	{
		CEGUI::Window* wnd = getLayout(layoutName);
		if (wnd != nullptr) {
			wnd->setSize(CEGUI::USize(CEGUI::UDim(x, 0), CEGUI::UDim(y, 0)));
		}
	}

	CEGUI::Window* UIManager::getLayout(std::string layoutName)
	{
		auto it = layouts.find(layoutName);

		if (it != layouts.end())
			return (*it).second;

		return nullptr;
	}

}
#include "UIManager.h"

#include <GraphicsManager.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/Window.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

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
		if (root != nullptr)
			root->destroy();
		CEGUI::System::getSingleton().destroyGUIContext(*guiContext);
		CEGUI::System::destroy();
		CEGUI::OgreRenderer::destroy(*renderer);
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

		//root->addChild(window);

		//TODO
		//aimai esto e sun ejemplo para que salga algo en la pantalla 
		//CEGUI::FrameWindow* wnd = (CEGUI::FrameWindow*)winMngr->createWindow("TaharezLook/FrameWindow", "Sample Window");
		//wnd->setPosition(CEGUI::UVector2(cegui_reldim(0.05f), cegui_reldim(0.05f)));
		//wnd->setSize(CEGUI::USize(cegui_reldim(0.2f), cegui_reldim(0.1f)));
		//wnd->setMaxSize(CEGUI::USize(cegui_reldim(1.0f), cegui_reldim(1.0f)));
		//wnd->setMinSize(CEGUI::USize(cegui_reldim(0.01f), cegui_reldim(0.01f)));
		//wnd->setText("HORNO works!");
		//wnd->activate();


	}

	void UIManager::deleteContext()
	{
		//Eliminamos todas las ventanas, destruimos el GUIContext y el render de ogre
		removeLayout();
		CEGUI::System::getSingleton().destroyGUIContext(*guiContext);
		renderer->destroySystem();
	}

	void UIManager::defineScheme(std::string schemeName)
	{
		if (!CEGUI::SchemeManager::getSingleton().isDefined(schemeName + ".scheme")) {
			CEGUI::SchemeManager::getSingleton().createFromFile(schemeName + ".scheme"); 
		}
		else {
			std::cout << "Already defined scheme!\n";
		}
	}

	void UIManager::removeLayout()
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
		CEGUI::System::getSingleton().getRenderer()->setDisplaySize(CEGUI::Size<float>(width, height));
	}

	void UIManager::update()
	{
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
		CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage(imageFile);

	}

	void UIManager::showMouseCursor()
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
	}

	void UIManager::hideMouseCursor()
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();
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

}
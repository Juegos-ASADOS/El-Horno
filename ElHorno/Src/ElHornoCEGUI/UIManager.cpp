#include "UIManager.h"
#include "UIElement.h"

#include <GraphicsManager.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/Window.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include <OgreRenderWindow.h>
#include "CheckML.h"

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


		//esto es la carga de recursos sobre como s eva a utilizar cegui (fuente de letra, letreros, puntero del raton etc etc)
		CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
		CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

	}

	void UIManager::erase()
	{
		delete instance_;
	}

	void UIManager::createRoot()
	{
		winMngr = CEGUI::WindowManager::getSingletonPtr();

		//Ventana por defecto a modo de GameObject
		//Todos los botones texto etc se crean dentro de esta misma ventana
		root = (CEGUI::DefaultWindow*)winMngr->createWindow("DefaultWindow", "Root");
		//root->setUsingAutoRenderingSurface(true);
		guiContext->setRootWindow(root);

		root->activate();
	}

	void UIManager::createContext()
	{
		//Seleccionamos el RenderTarget que usamos de ogre que usamos de Root de Renderizado
		renderer = &CEGUI::OgreRenderer::bootstrapSystem(*GraphicsManager::getInstance()->getRenderWindow());

		//Creo que se crea así
		guiContext = &CEGUI::System::getSingleton().createGUIContext(renderer->getDefaultRenderTarget());

		//CEGUI::SchemeManager::getSingleton().createFromFile("Layouts");
		//esto para que no se haga en la constructora
		setUpResources();

		createRoot();

		//TODO
		//aimai esto e sun ejemplo para que salga algo en la pantalla 
		//CEGUI::FrameWindow* wnd = (CEGUI::FrameWindow*)winMngr->createWindow("TaharezLook/FrameWindow", "Sample Window");
		//root->addChild(wnd);
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
		winMngr->destroyAllWindows();
		CEGUI::System::getSingleton().destroyGUIContext(*guiContext);
		renderer->destroySystem();
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

	//Para cambiar la imagen del ratón
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

	CEGUI::DefaultWindow* UIManager::getRoot()
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

	void UIManager::setVisibleLayout(bool visible, int layout)
	{
		layouts[layout]->setVisible(visible);
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

	std::vector<CEGUI::Window*> UIManager::getLayouts()
	{
		return layouts;
	}
}
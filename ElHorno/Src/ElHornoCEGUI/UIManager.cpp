#include "UIManager.h"
#include "UIElement.h"

#include <GraphicsManager.h>
#include <CEGUI/CEGUI.h>
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
		CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
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
	}

	void UIManager::createContext()
	{
		//Seleccionamos el RenderTarget que usamos de ogre que usamos de Root de Renderizado
		renderer = &CEGUI::OgreRenderer::bootstrapSystem(*GraphicsManager::getInstance()->getRenderWindow());

		//Creo que se crea así
		guiContext = &CEGUI::System::getSingleton().createGUIContext(renderer->getDefaultRenderTarget());

		//esto para que no se haga en la constructora
		setUpResources();

		createRoot();

		//CEGUI::SchemeManager::createFromFile();
		//CEGUI::FrameWindow* frame = static_cast<CEGUI::FrameWindow*>(winMngr->createWindow());
		//CEGUI::Window* statictext = static_cast<CEGUI::DefaultWindow*>(winMngr->createWindow(winMngr->GeneratedWindowNameBase));

		/*layouts.push_back(new CEGUI::Window("text", "prueba"));
		layouts[0]->setText("probandole");
		layouts[0]->setPosition(CEGUI::UVector2(CEGUI::UDim(3.0f,0.0f), (CEGUI::UDim(3.0f, 0.0f))));
		layouts[0]->activate();*/

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
		CEGUI::System::getSingleton().renderAllGUIContexts();
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
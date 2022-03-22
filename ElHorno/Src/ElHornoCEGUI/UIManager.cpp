#include "UIManager.h"
#include "UIElement.h"

#include <GraphicsManager.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include <OgreRenderWindow.h>

UIManager* UIManager::instance = 0;

UIManager::UIManager(Ogre::RenderWindow* renderWindow)
{
	CEGUI::OgreRenderer& auxiliar = CEGUI::OgreRenderer::bootstrapSystem(*GraphicsManager::getInstance()->getRenderWindow());
	renderer = &auxiliar;
	createRoot();

	
}

UIManager::~UIManager()
{
}

UIManager* UIManager::getInstance()
{
	return instance;
}


bool UIManager::setupInstance(Ogre::RenderWindow* window)
{
	if (instance == 0)
	{
		instance = new UIManager(window);
		return true;
	}

	return false;
}

void UIManager::clean()
{
	delete instance;
}

void UIManager::createRoot()
{
}

void UIManager::changeScreenSize(int width, int height)
{
	CEGUI::System::getSingleton().getRenderer()->setDisplaySize(CEGUI::Size<float>(width, height));
}

void UIManager::update()
{
}

void UIManager::changeText(CEGUI::Window* window, std::string text)
{
	window->setText(text);
}

//Para cambiar el ratón
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

UIElement* UIManager::getRoot()
{
	return root;
}

CEGUI::Window* UIManager::getWindow(const std::string& name )
{
	//Si no fuciona intentar static_Cast
	return root->getWindowElement()->getChild(name);
}

CEGUI::WindowManager* UIManager::getWinMngr()
{
	return winMngr;
}

void UIManager::setVisibleLayout(bool visible, int layout)
{
	layouts[layout]->setVisible(visible);
}

void UIManager::changeAlpha(const std::string & imagePath, float alpha)
{
	//Si sale error hacer static_cast
	CEGUI::Window* thumbnail = root->getWindowElement()->getChild(imagePath);
	thumbnail->setAlpha(alpha);
}

float UIManager::getAlpha(const std::string & namePath )
{
	//Si sale error hacer static_cast
	CEGUI::Window* thumbnail = root->getWindowElement()->getChild(namePath);
	return thumbnail->getAlpha();
}

std::vector<CEGUI::Window*> UIManager::getLayouts()
{
	return layouts;
}

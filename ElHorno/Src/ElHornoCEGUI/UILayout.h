#pragma once
#ifndef UI_LAYOUT_H
#define UI_LAYOUT_H

#include "Component.h"
#include <unordered_map>

#include <functional>

namespace CEGUI {
	class Window;
	class EventArgs;
}

namespace El_Horno {
	class UIManager;

	class _declspec(dllexport) UILayout : public Component
	{
	private:
		UIManager* uiManager;

		std::unordered_map<std::string, CEGUI::Window*> layouts;
	public:
		UILayout();
		~UILayout();

		void start() override;
		void setParameters(std::vector<std::pair<std::string, std::string>> parameters) override;

		void setLayoutVisibility(std::string layoutName, bool visible);
		//void setLayoutVisibility(int layout, bool visible);

		void addLayout(std::string layoutName, std::string name = "");
		void removeLayout(std::string layoutName);
		//void removeLayout(int layout);


		void removeLayouts();
		void loadScheme(std::string shcemeName);

		void setScale(std::string layoutName, float x, float y);
		//void setScale(int layout, float x, float y);

		void subscribeChildEvent(std::string layoutName, std::string childName, std::function<bool(const CEGUI::EventArgs&)> func);


		
		template<class T>
		void subscribeChildEvent(std::string layoutName, std::string childName, void (T::*func)(), T* comp);

		void subscribeChildEvent(std::string layoutName, std::string childName, bool (*func)());
		void subscribeChildEvent(std::string layoutName, std::string childName, bool (*func)(const CEGUI::EventArgs& e));
		//void subscribeChildEvent(int layout, std::string childName, bool (*func)());

		void addImageFile(const std::string& imageName, const std::string& imageFile);

		void addWidgetToLayout(const std::string& layoutName, const std::string& childName, const std::string& widgetType);
		void removeWidgetFromLayout(const std::string& layoutName, const std::string& childPath);

		void addProperty();
		void setChildProperty(const std::string& layoutName, const std::string& childPath, const std::string& propertyName, const std::string& values);

	private:
		CEGUI::Window* getLayout(std::string layoutName);
		//CEGUI::Window* getLayout(int layout);
		//void createButton(const std::string& scheme, const std::string& type, const std::string& name);

		//bool onClick(const CEGUI::EventArgs& e);

	};
}
#endif UI_LAYOUT_H
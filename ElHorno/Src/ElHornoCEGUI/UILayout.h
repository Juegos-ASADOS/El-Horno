#pragma once
#ifndef UI_LAYOUT_H
#define UI_LAYOUT_H

#include "Component.h"

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

		std::vector<CEGUI::Window*> layouts;
	public:
		UILayout();
		~UILayout();

		void start() override;
		void setParameters(std::vector<std::pair<std::string, std::string>> parameters) override;

		void setLayoutVisibility(std::string layoutName, bool visible);
		void setLayoutVisibility(int layout, bool visible);

		void addLayout(std::string layoutName, std::string name);
		void removeLayout(std::string layoutName);
		void removeLayout(int layout);

		void removeLayouts();
		
		void loadScheme(std::string shcemeName);

		void setScale(std::string layoutName, float x, float y);
		void setScale(int layout, float x, float y);


		void subscribeChildEvent(std::string layoutName, std::string childName, bool (*func)());
		void subscribeChildEvent(int layout, std::string childName, bool (*func)());

	private:
		CEGUI::Window* getLayout(std::string layoutName);
		CEGUI::Window* getLayout(int layout);
		//void createButton(const std::string& scheme, const std::string& type, const std::string& name);

		//bool onClick(const CEGUI::EventArgs& e);

	};
}
#endif UI_LAYOUT_H
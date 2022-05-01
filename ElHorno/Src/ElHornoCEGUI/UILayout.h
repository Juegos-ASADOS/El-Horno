#pragma once
#ifndef UI_LAYOUT_H
#define UI_LAYOUT_H

#include "Component.h"

namespace CEGUI {
	class Window;
}

namespace El_Horno {
	class UIManager;

	class _declspec(dllexport) UILayout : public Component
	{
	private:
		std::string layoutName_;
		std::string name_;

		UIManager* uiManager;

		CEGUI::Window* layoutRoot = nullptr;
	public:
		UILayout(std::string layoutName, std::string name);
		UILayout() {};
		~UILayout();

		void start() override;

		void setParameters(std::vector<std::pair<std::string, std::string>> parameters) override;
		
		void loadScheme(std::string shcemeName);
		void loadLayout();

		void removeLayout();

		void subscribeChildEvent(std::string childName, bool (*func)());

		void changeLayout(std::string layoutName, std::string name);
	};
}
#endif UI_LAYOUT_H
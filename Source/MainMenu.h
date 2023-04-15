#pragma once

#include "GameEngine.h"

class MainMenu
{
	private:
		int selected;
		Text* marked;

		// Main menu
		Text menu_selection[5];

		// Options
		Text options_selection[1];

	public:
		MainMenu();
		~MainMenu();

		// Scenes handling
		int scene;
		bool initialize_scene;

		// Create scene
		void CreateMainMenu();
		void CreateOptions();

		// Update scene
		void UpdateMainMenu();
		void UpdateOptions();

		// Render scene
		void RenderMainMenu();
		void RenderOptions();
};

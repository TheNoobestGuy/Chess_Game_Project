#include "MainMenu.h"

MainMenu::MainMenu()
{
	this->selected = 0;
	this->marked = nullptr;
	this->scene = 0;
	this->initialize_scene = true;

	for (int i = 0; i < 5; i++)
	{
		menu_selection[i] = { nullptr, { 255, 255, 255 }, NULL };
	}

	for (int i = 0; i < 1; i++)
	{
		options_selection[i] = { nullptr, { 255, 255, 255 }, NULL };
	}

}

MainMenu::~MainMenu() {}

void MainMenu::CreateMainMenu()
{
	menu_selection[0].text = "Chess Game Project";
	menu_selection[0].rect = GameEngine::CreateRectangle(SCREEN_WIDTH/2 - 200, 60, 400, 100);

	menu_selection[1].text = "Start Game";
	menu_selection[1].rect = GameEngine::CreateRectangle(SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 70, 200, 50);

	menu_selection[2].text = "Options";
	menu_selection[2].rect = GameEngine::CreateRectangle(SCREEN_WIDTH/2 - 60, SCREEN_HEIGHT/2 - 20, 120, 50);

	menu_selection[3].text = "Exit Game";
	menu_selection[3].rect = GameEngine::CreateRectangle(SCREEN_WIDTH/2 - 80, SCREEN_HEIGHT/2 + 30, 160, 50);

	menu_selection[4].text = "Author: Maciej Kaptur";
	menu_selection[4].rect = GameEngine::CreateRectangle(SCREEN_WIDTH - 190, SCREEN_HEIGHT - 45, 180, 40);
}

void MainMenu::CreateOptions()
{
	options_selection[0].text = "Back";
	options_selection[0].rect = GameEngine::CreateRectangle(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 45, 90, 40);
}

void MainMenu::UpdateMainMenu()
{
	// Check for selection from menu
	for (int select = 1; select < 4; select++)
	{
		if (marked == nullptr)
		{
			if (GameEngine::CollisionDetector(GameEngine::mouse_x, GameEngine::mouse_y, &menu_selection[select].rect))
			{
				menu_selection[select].color = { 255, 0, 0 };
				marked = &menu_selection[select];
				selected = select;
			}
		}
		else
		{
			if (!GameEngine::CollisionDetector(GameEngine::mouse_x, GameEngine::mouse_y, &marked->rect))
			{
				marked->color = { 255, 255, 255 };
				marked = nullptr;
				selected = 0;
			}
			else
			{
				if (GameEngine::mouse_left)
				{
					scene = selected;
					break;
				}
			}
		}
	}
}

void MainMenu::UpdateOptions()
{
	// Check for selection from options
	for (int select = 0; select < 1; select++)
	{
		if (marked == nullptr)
		{
			if (GameEngine::CollisionDetector(GameEngine::mouse_x, GameEngine::mouse_y, &options_selection[select].rect))
			{
				options_selection[select].color = { 255, 0, 0 };
				marked = &options_selection[select];
				selected = select;
			}
		}
		else
		{
			if (!GameEngine::CollisionDetector(GameEngine::mouse_x, GameEngine::mouse_y, &marked->rect))
			{
				marked->color = { 255, 255, 255 };
				marked = nullptr;
				selected = 0;
			}
			else
			{
				if (GameEngine::mouse_left)
				{
					scene = selected;
					break;
				}
			}
		}
	}
}

void MainMenu::RenderMainMenu()
{
	SDL_RenderClear(GameEngine::renderer);

	for (Text& selection : menu_selection)
	{
		TextureMenager::DrawText(selection);
	}

	SDL_RenderPresent(GameEngine::renderer);
}

void MainMenu::RenderOptions()
{
	SDL_RenderClear(GameEngine::renderer);

	for (Text& selection : options_selection)
	{
		TextureMenager::DrawText(selection);
	}

	SDL_RenderPresent(GameEngine::renderer);
}
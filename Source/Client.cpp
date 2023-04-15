#include "Scenes.h"

GameEngine* game_engine = nullptr;

// Pointers to scenes
MainMenu* main_menu = nullptr;
Chessboard* chessboard = nullptr;

int main(int argc, char* args[])
{
	// Timer
	int const frameDelay = 1000 / FPS;    // (Time delay for one frame) = (1000)/(frames per second)
	Uint32 frameStart;
	int deltaTime;

	// Game Initialising
	game_engine = new GameEngine();
	game_engine->Init("Chess Game Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_FULLSCREEN);

	// Game Loop
	GameEngine::stage = 0;
	GameEngine::initialize_stage = true;

	while (game_engine->Running())
	{
		frameStart = SDL_GetTicks();

		// Game engine featuresa
		game_engine->EventHandler();

		// Stages
		switch (GameEngine::stage)
		{
			// Main menu
			case 0:
				if (GameEngine::initialize_stage)
				{
					std::cout << "Main menu initialized!" << std::endl;
					main_menu = new MainMenu();
					GameEngine::initialize_stage = false;
				}

				Main_menu_scene(main_menu);

				if (GameEngine::stage != 0)
				{
					main_menu = nullptr;
					GameEngine::initialize_stage = true;
				}
				break;

			// Chessboard
			case 1:
				if (GameEngine::initialize_stage)
				{
					std::cout << "Chessboard initialized!" << std::endl;
					chessboard = new Chessboard(64);
					chessboard->CreateBoard();
					chessboard->CreateFigures();

					GameEngine::initialize_stage = false;
				}

				Chessboard_scene(chessboard);

				if (GameEngine::stage != 1)
				{
					chessboard = nullptr;
					GameEngine::initialize_stage = true;
				}
				break;

			default:
				GameEngine::isRunning = false;
				break;
		}

		deltaTime = SDL_GetTicks() - frameStart;

		// Frame Delay
		if (frameDelay > deltaTime)
		{
			SDL_Delay(frameDelay - deltaTime);
		}
	}
	
	game_engine->Clean();

	return 0;
}

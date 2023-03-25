#include "GameEngine.h"

GameEngine* game = nullptr;

int main(int argc, char* args[])
{
	// Timer
	const int FPS = 120;
	const int frameDelay = 1000 / FPS;    // (Time delay for one frame) = (1000)/(frames per second)
	Uint32 frameStart;
	int deltaTime;

	// Game Initialising
	game = new GameEngine();
	game->Init("Chess Game Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, false);

	// Game Loop
	while (game->Running())
	{
		frameStart = SDL_GetTicks();

		// Engine Functions
		game->EventsHandler();
		game->Update();
		game->Render();

		deltaTime = SDL_GetTicks() - frameStart;

		// Frame Delay
		if (frameDelay > deltaTime)
		{
			SDL_Delay(frameDelay - deltaTime);
		}
	}
	
	game->Clean();

	return 0;
}

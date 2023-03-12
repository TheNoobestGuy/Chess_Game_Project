#include "GameEngine.h"

Game* game = nullptr;

int main(int argc, char* args[])
{
	// Timer
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;    // (Time delay for one frame) = (1000)/(frames per second)
	Uint32 frameStart;
	int deltaTime;

	// Game Initialising
	game = new Game();
	game->Init("Chess Game Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

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
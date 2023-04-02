#include "GameEngine.h"
#include "Chessboard.h"

GameEngine* game_engine = nullptr;
Chessboard* chessboard = nullptr;

int main(int argc, char* args[])
{
	// Timer
	const int FPS = 120;
	const int frameDelay = 1000 / FPS;    // (Time delay for one frame) = (1000)/(frames per second)
	Uint32 frameStart;
	int deltaTime;

	// Game Initialising
	game_engine = new GameEngine();
	game_engine->Init("Chess Game Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, false);

	// Chessboard
	chessboard = new Chessboard(64);
	chessboard->CreateBoard();
	chessboard->CreateFigures();

	// Game Loop
	while (game_engine->Running())
	{
		frameStart = SDL_GetTicks();

		// Game engine features
		game_engine->EventHandler();

		// Chessboard
		chessboard->BoardUpdate();
		chessboard->UpdateFigures();
		chessboard->RenderFigures();
		chessboard->SwitchTurns();
		

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

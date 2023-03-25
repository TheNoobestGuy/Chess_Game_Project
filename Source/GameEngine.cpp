// Core
#include "GameEngine.h"
#include "TextureMenager.h"

// Assets
#include "Chessboard.h"
#include "Pawn.h"

// Renderer
SDL_Renderer* Game::renderer = nullptr;

// Chessboard
Chessboard* chessboard;

// White player figures
Pawn* white_pawn_1;
Pawn* white_pawn_2;
Pawn* white_pawn_3;
Pawn* white_pawn_4;
Pawn* white_pawn_5;
Pawn* white_pawn_6;
Pawn* white_pawn_7;
Pawn* white_pawn_8;

// Black player figures
Pawn* black_pawn_1;
Pawn* black_pawn_2;
Pawn* black_pawn_3;
Pawn* black_pawn_4;
Pawn* black_pawn_5;
Pawn* black_pawn_6;
Pawn* black_pawn_7;
Pawn* black_pawn_8;

// Functions
Game::Game() {}

Game::~Game() {}

void Game::Init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		printf("Subsystem Initialised!\n");

		// Window Creating
		window = SDL_CreateWindow(title, x, y, width, height, flags);

		if (window)
		{
			printf("Windows had been created!\n");

			// Window Renderer
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer)
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				printf("Renderer has been created!\n");

				isRunning = true;
			}
			else
			{
				printf("Render couldn't be created: %s\n", SDL_GetError());
				isRunning = false;
			}
		}
		else
		{
			printf("Window couldn't be created: %s\n", SDL_GetError());
			isRunning = false;
		}

		// Chessboard
		chessboard = new Chessboard();

		// White player figures initialization
		white_pawn_1 = new Pawn(7, 1, 0, 0);
		white_pawn_2 = new Pawn(7, 2, 0, 0);
		white_pawn_3 = new Pawn(7, 3, 0, 0);
		white_pawn_4 = new Pawn(7, 4, 0, 0);
		white_pawn_5 = new Pawn(7, 5, 0, 0);
		white_pawn_6 = new Pawn(7, 6, 0, 0);
		white_pawn_7 = new Pawn(7, 7, 0, 0);
		white_pawn_8 = new Pawn(7, 8, 0, 0);

		// Black player figures initialization
		black_pawn_1 = new Pawn(2, 1, 1, 0);
		black_pawn_2 = new Pawn(2, 2, 1, 0);
		black_pawn_3 = new Pawn(2, 3, 1, 0);
		black_pawn_4 = new Pawn(2, 4, 1, 0);
		black_pawn_5 = new Pawn(2, 5, 1, 0);
		black_pawn_6 = new Pawn(2, 6, 1, 0);
		black_pawn_7 = new Pawn(2, 7, 1, 0);
		black_pawn_8 = new Pawn(2, 8, 1, 0);
	}
	else
	{
		printf("Subsystem failed to initialise: %s\n", SDL_GetError());
		isRunning = false;
	}
}

void Game::EventsHandler()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
	}
}

void Game::Update()
{
	// White player figures
	white_pawn_1->Update();
	white_pawn_2->Update();
	white_pawn_3->Update();
	white_pawn_4->Update();
	white_pawn_5->Update();
	white_pawn_6->Update();
	white_pawn_7->Update();
	white_pawn_8->Update();

	// Black player figures
	black_pawn_1->Update();
	black_pawn_2->Update();
	black_pawn_3->Update();
	black_pawn_4->Update();
	black_pawn_5->Update();
	black_pawn_6->Update();
	black_pawn_7->Update();
	black_pawn_8->Update();
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	chessboard->DrawBoard();

	// White player figures
	white_pawn_1->Render();
	white_pawn_2->Render();
	white_pawn_3->Render();
	white_pawn_4->Render();
	white_pawn_5->Render();
	white_pawn_6->Render();
	white_pawn_7->Render();
	white_pawn_8->Render();

	// Black player figures
	black_pawn_1->Render();
	black_pawn_2->Render();
	black_pawn_3->Render();
	black_pawn_4->Render();
	black_pawn_5->Render();
	black_pawn_6->Render();
	black_pawn_7->Render();
	black_pawn_8->Render();

	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Game Successfully Closed!\n");
}

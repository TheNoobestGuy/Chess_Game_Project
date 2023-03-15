#include "GameEngine.h"
#include "TextureMenager.h"
#include "GameObject.h"

// Renderer
SDL_Renderer* Game::renderer = nullptr;

// Figures
GameObject* pawn;

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
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
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

		// Figures
		pawn = new GameObject("Textures/Figures/pawn.png", 0, 0);
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
	pawn->Update();
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	// Renders
	pawn->Render();

	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Game Successfully Closed!\n");
}

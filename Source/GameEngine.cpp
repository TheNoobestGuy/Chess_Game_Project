// Core
#include "GameEngine.h"
#include "TextureMenager.h"

// Assets
#include "Chessboard.h"
#include "Pawn.h"

// Mouse tracer
int mouse_x, mouse_y;
bool mouse_left_click_hold = false;

// Picked figure
bool picked = false;
Figure* current_picked_pawn = nullptr;

// Chessboard
const int figures_number = 8;
Chessboard* chessboard = nullptr;

// Players figures
Figure* white_player[figures_number];
Figure* black_player[figures_number];
Figure* figure = nullptr;

// Renderer
SDL_Renderer* GameEngine::renderer = nullptr;

// Functions
GameEngine::GameEngine()
{
	// Mouse tracer
	mouse_x = 0;
	mouse_y = 0;
	mouse_left_click_hold = false;
}

GameEngine::~GameEngine() {}

void GameEngine::Init(const char* title, int x, int y, int width, int height, bool fullscreen)
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
	}
	else
	{
		printf("Subsystem failed to initialise: %s\n", SDL_GetError());
		isRunning = false;
	}

	// Objects inistializations

	// Chessboard
	chessboard = new Chessboard();

	// White player figures
	for (int i = 0; i < figures_number; i++)
	{
		figure = new Pawn(7, i+1, 0, 0);
		white_player[i] = figure;
	}

	// Black player figures
	for (int i = 0; i < figures_number; i++)
	{
		figure = new Pawn(2, i+1, 0, 0);
		black_player[i] = figure;
	}

	figure = nullptr;
}

void GameEngine::EventsHandler()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	// Mouse position
	SDL_GetMouseState(&mouse_x, &mouse_y);

	// Collisions with mouse
	std::vector<bool> figures_collisions;

	for (int i = 0; i < figures_number; i++)
	{
		figures_collisions.push_back(white_player[i]->MouseColliding(mouse_x, mouse_y, white_player[i]->RectGetter()));
	}

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_MOUSEBUTTONDOWN:
		mouse_left_click_hold = true;
		break;

	case SDL_MOUSEBUTTONUP:
		mouse_left_click_hold = false;
		break;

	default:
		break;
	}

	// Motion of figures
	Figure* current_picked = nullptr;

	for (int i = 0; i < figures_number; i++)
	{
		if (figures_collisions[i] && mouse_left_click_hold && !picked)
		{
			white_player[i]->InMotionSetter(true);

			current_picked_pawn = white_player[i];
			picked = true;
		}
	}

	if (!mouse_left_click_hold)
	{
		for (int i = 0; i < figures_number; i++)
		{
			white_player[i]->InMotionSetter(false);
			black_player[i]->InMotionSetter(false);
		}

		current_picked_pawn = nullptr;
		picked = false;
	}
}

void GameEngine::Update()
{
	white_player[0]->Update();
	
	// White player figures
	for (Figure* figure : white_player)
	{
		figure->Update();
	}

	// Black player figures
	for (Figure* figure : black_player)
	{
		figure->Update();
	}
}

void GameEngine::Render()
{
	SDL_RenderClear(renderer);

	// Chessboard
	chessboard->DrawBoard();

	// White player figures
	for (Figure* figure : white_player)
	{
		figure->Render();
	}

	// Black player figures
	for (Figure* figure : black_player)
	{
		figure->Render();
	}

	// Picked figure
	if (picked && current_picked_pawn != nullptr)
		current_picked_pawn->Render();

	SDL_RenderPresent(renderer);
}

void GameEngine::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Game Successfully Closed!\n");
}

int GameEngine::GetMouseX() { return mouse_x; }

int GameEngine::GetMouseY() { return mouse_y; }

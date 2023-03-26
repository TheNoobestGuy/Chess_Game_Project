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
Figure* current_picked_figure = nullptr;

// Chessboard Settings
int set_of_figure = 0;
int color_of_figure = 0;
const int figures_number = 8;
Chessboard* chessboard = nullptr;

// Players figures
Figure* figure = nullptr;
Figure* white_player[figures_number];
Figure* black_player[figures_number];

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

	// Objects initializations
	ObjectsInistializer();
}

void GameEngine::ObjectsInistializer()
{
	// Chessboard
	chessboard = new Chessboard();

	// White player figures
	for (int i = 0; i < figures_number; i++)
	{
		figure = new Pawn(7, i + 1, set_of_figure, color_of_figure);
		white_player[i] = figure;
	}

	// Black player figures
	for (int i = 0; i < figures_number; i++)
	{
		figure = new Pawn(2, i + 1, set_of_figure, color_of_figure);
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

	// Evenets switch handler
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
	for (int i = 0; i < figures_number; i++)
	{
		if (figures_collisions[i] && mouse_left_click_hold && !picked)
		{
			white_player[i]->InMotionSetter(true);

			current_picked_figure = white_player[i];
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

		current_picked_figure = nullptr;
		picked = false;
	}
}

void GameEngine::Update()
{
	// Figures Updates
	for (int i = 0; i < figures_number; i++)
	{
		white_player[i]->Update();
		black_player[i]->Update();
	}

}

void GameEngine::Render()
{
	SDL_RenderClear(renderer);

	// Chessboard
	chessboard->DrawBoard();

	// Figures Render
	for (int i = 0; i < figures_number; i++)
	{
		white_player[i]->Render();
		black_player[i]->Render();
	}

	// Picked figure
	if (picked && current_picked_figure != nullptr)
		current_picked_figure->Render();

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

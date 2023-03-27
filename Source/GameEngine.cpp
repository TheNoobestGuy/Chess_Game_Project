// Core
#include "GameEngine.h"
#include "TextureMenager.h"

// Assets
#include "Chessboard.h"
#include "Pawn.h"

// Chessboard Settings
int current_player = 0;
int set_of_figure = 0;
const int figures_number = 8;
Chessboard* chessboard = nullptr;

// Mouse properties
int mouse_x = 0;
int mouse_y = 0;
bool mouse_left_click_hold = false;

// Players figures
bool picked = false;
Figure* figure = nullptr;
Figure* white_player[figures_number];
Figure* black_player[figures_number];
Figure* current_picked_figure = nullptr;

// Renderer
SDL_Renderer* GameEngine::renderer = nullptr;

// Functions
GameEngine::GameEngine() {}

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
}

void GameEngine::ObjectsInistializer()
{
	// Chessboard
	chessboard = new Chessboard();

	// Appending of players figures into proper arrays
	for (int i = 0; i < figures_number; i++)
	{
		// White player figures
		figure = new Pawn(7, i + 1, 0, set_of_figure);
		white_player[i] = figure;

		// Black player figures
		figure = new Pawn(2, i + 1, 1, set_of_figure);
		black_player[i] = figure;
	}
	figure = nullptr;
}

void GameEngine::EventsHandler()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	// Collisions with mouse
	std::vector<bool> figures_collisions;

	if (current_player == 0)
	{
		for (int i = 0; i < figures_number; i++)
		{
			figures_collisions.push_back(GameEngine::CollisionDetector(mouse_x, mouse_y, white_player[i]->RectGetter()));
		}
	}
	else if (current_player == 1)
	{
		for (int i = 0; i < figures_number; i++)
		{
			figures_collisions.push_back(GameEngine::CollisionDetector(mouse_x, mouse_y, black_player[i]->RectGetter()));
		}
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
	if (current_player == 0)
	{
		for (int i = 0; i < figures_number; i++)
		{
			if (figures_collisions[i] && !picked)
			{
				white_player[i]->InMotionSetter(true);

				current_picked_figure = white_player[i];
				picked = true;
			}
		}
	}
	else if (current_player == 1)
	{
		for (int i = 0; i < figures_number; i++)
		{
			if (figures_collisions[i] && !picked)
			{
				black_player[i]->InMotionSetter(true);

				current_picked_figure = black_player[i];
				picked = true;
			}
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

void GameEngine::MouseTracer()
{
	SDL_GetMouseState(&mouse_x, &mouse_y);
}
int GameEngine::MouseGetX() { return mouse_x; }
int GameEngine::MouseGetY() { return mouse_y; }

void GameEngine::SetCurrentPlayer(int player)
{
	current_player = player;
}

SDL_Rect GameEngine::CreateRectangle(int pos_x, int pos_y, int size)
{
	SDL_Rect rect;

	rect.x = pos_x * size;
	rect.y = pos_y * size;
	rect.w = rect.h = size;

	return rect;
}

void GameEngine::RectangleHandler(SDL_Rect* srcRect, SDL_Rect* destRect, int src_size, int dest_size)
{
	// Source size and position of image
	srcRect->w = src_size;
	srcRect->h = src_size;
	srcRect->x = srcRect->y = 0;

	// Destinated size and position of image
	destRect->w = destRect->h = dest_size;
}

bool GameEngine::CollisionDetector(SDL_Rect* first_object, SDL_Rect* second_object)
{
	if (first_object->x + 32 >= second_object->x && first_object->x + 32 <= (second_object->x + second_object->w))
	{
		if (first_object->y + 32 >= second_object->y && first_object->y + 32<= (second_object->y + second_object->h)) {
			return true;
		}
	}
	return false;
}

bool GameEngine::CollisionDetector(int x_coordinate, int y_coordinate, SDL_Rect* second_object)
{
	if (x_coordinate >= second_object->x && x_coordinate <= (second_object->x + second_object->w))
	{
		if (y_coordinate >= second_object->y && y_coordinate <= (second_object->y + second_object->h)) {
			return true;
		}
	}
	return false;
}
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
Pawn* current_picked_pawn = nullptr;

// Renderer
SDL_Renderer* GameEngine::renderer = nullptr;

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

void GameEngine::EventsHandler()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	// Mouse position
	SDL_GetMouseState(&mouse_x, &mouse_y);

	// Collisions
	bool figures_collisions[8] =
	{
		white_pawn_1->MouseColliding(mouse_x, mouse_y, white_pawn_1->RectGetter()),
		white_pawn_2->MouseColliding(mouse_x, mouse_y, white_pawn_2->RectGetter()),
		white_pawn_3->MouseColliding(mouse_x, mouse_y, white_pawn_3->RectGetter()),
		white_pawn_4->MouseColliding(mouse_x, mouse_y, white_pawn_4->RectGetter()),
		white_pawn_5->MouseColliding(mouse_x, mouse_y, white_pawn_5->RectGetter()),
		white_pawn_6->MouseColliding(mouse_x, mouse_y, white_pawn_6->RectGetter()),
		white_pawn_7->MouseColliding(mouse_x, mouse_y, white_pawn_7->RectGetter()),
		white_pawn_8->MouseColliding(mouse_x, mouse_y, white_pawn_8->RectGetter())
	};

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_MOUSEMOTION:
		std::cout << "Mouse coord: " << mouse_x << ", " << mouse_y << std::endl;
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

	if (figures_collisions[0] && mouse_left_click_hold)
	{
		white_pawn_1->InMotionSetter(true);

		current_picked_pawn = white_pawn_1;
		picked = true;
	}

	if (!mouse_left_click_hold)
	{
		white_pawn_1->InMotionSetter(false);

		current_picked_pawn = nullptr;
		picked = false;
	}
}

void GameEngine::Update()
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

void GameEngine::Render()
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

	// Current picked object
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

int GameEngine::GetMouseX()
{
	return mouse_x;
}

int GameEngine::GetMouseY()
{
	return mouse_y;
}

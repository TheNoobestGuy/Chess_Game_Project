#include <SDL.h>
#include <stdio.h>

// Screen dimension
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not be initialized.");
		SDL_GetError();
	}
	else
	{
		// Window creation
		window = SDL_CreateWindow("Chess Game Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		// Keyboard state snapshot
		const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);

		// Game loop
		bool exit_game = false;

		while (exit_game == false)
		{
			SDL_Event event;

			// Event loop
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					exit_game = true;
				if (event.type == SDL_KEYDOWN)
				{
					if (event.key.keysym.sym == SDLK_0)
						printf("pressed 0\n");
				}

				if (keyboard_state[SDL_SCANCODE_RIGHT])
					printf("Right arrow key is pressed\n");
			}
		}

		SDL_DestroyWindow(window);
	}

	SDL_Quit();
	return 0;
}

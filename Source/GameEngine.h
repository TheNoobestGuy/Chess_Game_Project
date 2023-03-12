#pragma once

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
class Game
{
	private:
		int counter;
		bool isRunning;
		SDL_Window* window;
		SDL_Renderer* renderer;

	public:
		Game();
		~Game();

		void Init(const char* title, int x, int y, int width, int height, bool fullscreen);
		
		void EventsHandler();
		void Update();
		void Render();
		void Clean();

		bool Running() { return isRunning; }
};
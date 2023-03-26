#pragma once

// Basic Libraries
#include <iostream>
#include <stdio.h>
#include <vector>
#include <tuple>

// SDL Libraries
#include <SDL.h>
#include <SDL_image.h>

class GameEngine
{
	private:
		bool isRunning;
		SDL_Window* window;

	public:
		GameEngine();
		~GameEngine();;

		void Init(const char* title, int x, int y, int width, int height, bool fullscreen);

		void ObjectsInistializer();
		void EventsHandler();
		void Update();
		void Render();
		void Clean();

		static int GetMouseX();
		static int GetMouseY();

		bool Running() { return isRunning; }

		static SDL_Renderer* renderer;
};
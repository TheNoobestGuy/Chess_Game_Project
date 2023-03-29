#pragma once

// Basic Libraries
#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>

// SDL Libraries
#include <SDL.h>
#include <SDL_image.h>

// Header files
#include "TextureMenager.h"

class GameEngine
{
	private:
		bool isRunning;
		SDL_Window* window;

	public:
		static SDL_Renderer* renderer;

		// Vital game functions
		void Init(const char* title, int x, int y, int width, int height, bool fullscreen);
		void EventHandler();
		void Clean();

		// Mouse handler
		static bool mouse_left;
		static int mouse_x;
		static int mouse_y;

		// Collisions handler
		static SDL_Rect CreateRectangle(int pos_x, int pos_y, int size);
		static bool CollisionDetector(SDL_Rect* first_object, SDL_Rect* second_object);
		static bool CollisionDetector(int &x_coordinate, int &y_coordinate, SDL_Rect* object);
		static void RectangleHandler(SDL_Rect* srcRect, SDL_Rect* destRect, int src_size, int dest_size);

		// State of game engine
		bool Running() { return isRunning; }
};


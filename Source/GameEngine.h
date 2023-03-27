#pragma once

// Basic Libraries
#include <iostream>
#include <stdio.h>
#include <vector>
#include <tuple>
#include <stack>

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
		~GameEngine();

		// Vital game objects
		static SDL_Renderer* renderer;

		void Init(const char* title, int x, int y, int width, int height, bool fullscreen);
		void ObjectsInistializer();
		void EventsHandler();
		void Update();
		void Render();
		void Clean();

		void MouseTracer();
		static int MouseGetX();
		static int MouseGetY();

		static void SetCurrentPlayer(int player);

		// Collisions handler
		static SDL_Rect CreateRectangle(int pos_x, int pos_y, int size);
		static bool CollisionDetector(SDL_Rect* first_object, SDL_Rect* second_object);
		static bool CollisionDetector(int x_coordinate, int y_coordinate, SDL_Rect* second_object);
		static void RectangleHandler(SDL_Rect* srcRect, SDL_Rect* destRect, int src_size, int dest_size);

		// State of game engine
		bool Running() { return isRunning; }
};
//FMT and string
#include <fmt/base.h>
#include <string>

//SDL
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_log.h>
#include <SDL_messagebox.h>
#include <SDL_events.h>
#include "FatalError.hpp"

int main(int argc, char* argv[]) {
	for (int ar = 0; ar < argc; ar++) {
		std::string a(argv[ar]);
		if (a.compare("--version") == 0 || a.compare("-v") == 0) {
			fmt::println("version 0.0.0");
			return 0;
		}
	}
	fmt::println("Initializing...");
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		Fatal::FATAL("SDL2 failed to initialize!", __FILE_NAME__, __LINE__, __FUNCTION__);
		return 1;
	}
	Uint32 renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_Window* win = SDL_CreateWindow("Callum's SDL2 thing!", 100, 100, 480, 360, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, renderFlags);
	if (win == nullptr) {
		Fatal::FATAL("Failed to create window!", __FILE_NAME__, __LINE__, __FUNCTION__);
	}
	if (renderer == nullptr) {
		Fatal::FATAL("Failed to create renderer!", __FILE_NAME__, __LINE__, __FUNCTION__);
	}
	bool running = true;
	SDL_Event e;
	while (running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = false;
			}

		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    	SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(renderer, 0, 0, 480, 360);
		SDL_RenderPresent(renderer);
	}
	SDL_Quit();
    return 0;
}
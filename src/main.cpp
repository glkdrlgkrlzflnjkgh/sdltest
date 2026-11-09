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

//My own stuff
#include "Log.hpp"


int main(int argc, char* argv[]) {
	Logging::Logger logger;
	for (int ar = 0; ar < argc; ar++) {
		std::string a(argv[ar]);
		if (a.compare("--version") == 0 || a.compare("-v") == 0) {
			fmt::println("version 0.0.0");
			return 0;
		}
	}
	// --- SDL INIT ---
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		Fatal::FATAL("SDL2 failed to initialize!", __FILE_NAME__, __LINE__, __FUNCTION__);
		return 1;
	}
	Uint32 renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	Uint32 windowFlags = SDL_WINDOW_HIDDEN;
	SDL_Window* win = SDL_CreateWindow("Callum's SDL2 thing!", 100, 100, 480, 360, windowFlags);
	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, renderFlags);
	if (!win) {
		Fatal::FATAL("Failed to create window!", __FILE_NAME__, __LINE__, __FUNCTION__);
	}
	if (!renderer) {
		Fatal::FATAL("Failed to create renderer!", __FILE_NAME__, __LINE__, __FUNCTION__);
	}
	// --- MAIN LOOP ---
	bool running = true;
	SDL_Event e;
	logger.log("Showing window!", Logging::LogLevel::INFO);
	SDL_ShowWindow(win);
	logger.log("Entering main loop!", Logging::LogLevel::INFO);
	while (running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				logger.log("Quit requested!", Logging::LogLevel::INFO);
				running = false;
			}

		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    	SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(renderer, 0, 0, 480, 360);
		SDL_RenderPresent(renderer);
	}
	logger.log("Destroying renderer....", Logging::LogLevel::INFO);
	SDL_DestroyRenderer(renderer);
	logger.log("Destroying window...", Logging::LogLevel::INFO);
	SDL_DestroyWindow(win);
	logger.log("Shutting down SDL2 :C", Logging::LogLevel::INFO);
	SDL_Quit();
	logger.log("Goodbye!", Logging::LogLevel::INFO);
    return 0;
}
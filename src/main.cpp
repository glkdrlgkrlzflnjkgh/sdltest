//FMT and string
#include <fmt/base.h>
#include <fmt/format.h>
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
	logger.log("Initializing!", Logging::LogLevel::INFO);
	for (int ar = 0; ar < argc; ar++) {
		std::string a(argv[ar]);
		if (a.compare("--version") == 0 || a.compare("-v") == 0) {
			fmt::println("version 0.0.0");
			return 0;
		}
	}
	// --- SDL INIT ---
	logger.log("Initializing SDL2...", Logging::LogLevel::INFO);
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		Fatal::FATAL("SDL2 failed to initialize!", __FILE_NAME__, __LINE__, __FUNCTION__);
		return 1;
	}
	logger.log("Creating window...", Logging::LogLevel::INFO);
	Uint32 renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	Uint32 windowFlags = SDL_WINDOW_HIDDEN;
	SDL_Window* win = SDL_CreateWindow("Callum's SDL2 thing!", 100, 100, 480, 360, windowFlags);
	if (!win) {
		Fatal::FATAL(SDL_GetError(), __FILE_NAME__, __LINE__, __FUNCTION__);
	}
	Uint64 start = SDL_GetPerformanceCounter();
	logger.log("Creating renderer...", Logging::LogLevel::INFO);
	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, renderFlags);
	if (!renderer) {
		Fatal::FATAL(SDL_GetError(), __FILE_NAME__, __LINE__, __FUNCTION__);
	}
	Uint64 end = SDL_GetPerformanceCounter();
	double ms =
		(double)(end - start) * 1000.0 /
		SDL_GetPerformanceFrequency();
	std::string out = fmt::format(
		"Renderer creation took {:.3f} ms",
		ms
	);
	logger.log(out, Logging::LogLevel::INFO);
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
		int x, y;
		Uint32 buttons = SDL_GetMouseState(&x, &y);
		SDL_Rect r;
		r.w = -20;
		r.h = -20;
		r.x = x;
		r.y = y;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    	SDL_RenderClear(renderer);
		bool changeCol = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
		if (changeCol) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		}
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_RenderFillRect(renderer, &r);
		SDL_RenderPresent(renderer);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
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
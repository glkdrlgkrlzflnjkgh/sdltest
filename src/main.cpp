#include <SDL_video.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>

int main() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal Error!", "SDL2 failed to initialize!", nullptr);
		return 1;
	}
	SDL_Window* win = SDL_CreateWindow("Callum's SDL2 thing!", 100, 100, 400, 600, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal Error!", "SDL2 failed to create a window!", nullptr);
	}
    return 0;
}
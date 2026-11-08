#define SDL_MAIN_HANDLED
#include <SDL.h>

int main() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}
    return 0;
}
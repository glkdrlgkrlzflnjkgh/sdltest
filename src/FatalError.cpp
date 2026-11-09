#include "FatalError.hpp"
#include <SDL_error.h>
#include <SDL_messagebox.h>
#include <fmt/base.h>
#include <string>
void Fatal::FATAL(const char* msg, const char* file, int line, const char* func) {
    std::string fullMsg = "FATAL: " + std::string(func) + " (" + std::string(file) + ":" + std::to_string(line) + ") - " + msg;
    if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal error!", fullMsg.c_str(), nullptr) != 0) {
         fmt::println("Failed to show dialog! {}", SDL_GetError());
    }
        
    fmt::println(fullMsg);
    abort();
}

#include "Log.hpp"
#include <fmt/core.h>

std::string toString(Logging::LogLevel l) {
    switch (l) {
        case Logging::LogLevel::INFO : return "[INFO]";
        case Logging::LogLevel::WARN: return "[WARN]";
        case Logging::LogLevel::ERROR: return "[ERROR]";
        case Logging::LogLevel::FATAL: return "[FATAL]";
        case Logging::LogLevel::DEBUG: return "[DEBUG]";
    }
    return "[???]";
}

void Logging::Logger::log(std::string m, LogLevel level) {
    fmt::println("{} {}", toString(level), m);
}
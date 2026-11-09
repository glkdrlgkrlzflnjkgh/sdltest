#pragma once
#include <string>
namespace Logging {
    enum class LogLevel {
        INFO,
        WARN,
        ERROR,
        FATAL,
        DEBUG,
    };
    class Logger {
        public:
            void log(std::string m, LogLevel level);
    };
}
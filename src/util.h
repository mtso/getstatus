#ifndef GS_UTIL
#define GS_UTIL

#include <string>
#include <chrono>

const int BUF_SIZE = 80;

namespace getstatus {

    std::string get_midnight() {
        auto now = std::chrono::system_clock::now();
        char buffer[BUF_SIZE];
        auto now_t = std::chrono::system_clock::to_time_t(now);
        auto fmt = std::strftime(
            buffer,
            BUF_SIZE,
            "%Y-%m-%dT00:00:00Z",
            std::localtime(&now_t)
        );
        
        return std::string(buffer);
    }
    
}

#endif

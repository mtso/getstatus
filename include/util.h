#ifndef GS_UTIL_H
#define GS_UTIL_H

#include <string>
#include <chrono>

#include <cstdlib>
#include <iostream>

const int BUF_SIZE = 80;

namespace getstatus {

    /// Returns the midnight timestamp in the GitLab API-accepted
    /// format: YYYY-MM-DDTHH:MM:SSZ
    std::string get_midnight() {
        auto now = std::chrono::system_clock::now();
        auto now_t = std::chrono::system_clock::to_time_t(now);
        char buffer[BUF_SIZE];

        // auto t = std::localtime(&now_t);
        // auto f = sprintf(buffer, "%02d-%02d-%02dT00:00:00Z", t->tm_year, t->tm_mon, t->tm_mday);
        // std::cout << std::string(buffer) << std::endl;
        // return std::string(buffer);
        auto fmt = std::strftime(
            buffer,
            BUF_SIZE,
            "%Y-%m-%dT00:00:00Z",
            std::localtime(&now_t)
        );

        return std::string(buffer);
    }

    std::string to_timestamp(std::chrono::time_point<std::chrono::system_clock> tz) {
        auto tz_t = std::chrono::system_clock::to_time_t(tz);
        char buffer[BUF_SIZE];
        auto fmt = std::strftime(
            buffer,
            BUF_SIZE,
            "%Y-%m-%dT00:00:00Z",
            std::localtime(&tz_t)
        );

        return std::string(buffer);
    }

} // namespace getstatus

#endif

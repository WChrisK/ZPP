#pragma once

#include "util/string/StringBuilder.hpp"

namespace Helion {

class Logger {
    StringBuilder messageBuilder;

    void end();

public:
    Logger& operator()();

    template <typename T, typename... Args>
    Logger& operator()(const T& t, Args&&... args) {
        messageBuilder(t);
        return operator()(std::forward<Args>(args)...);
    }
};

extern Logger Log;

}

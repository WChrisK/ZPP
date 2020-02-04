#include "doomtype.h"
#include "util/Logging.hpp"

namespace Helion {

Logger Log;

Logger& Logger::operator()() {
    end();
    return *this;
}

void Logger::end() {
    const String message = messageBuilder.toString();
    Printf(message.getChars());

    if (not message.empty())
        messageBuilder.clear();
}

}

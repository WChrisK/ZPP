#pragma once

#include <stdexcept>
#include "helion/util/string/String.hpp"

namespace Helion {

/**
 * The generic exception class for this project that all other exceptions must
 * extend from.
 */
class Exception : std::runtime_error {
protected:
    String reason;

public:
    explicit Exception(const String& reason) :
            runtime_error(reason.getChars()),
            reason(reason) {
    }

    ~Exception() override = default;

    const String& getReason() const {
        return reason;
    }
};

#define CUSTOM_EXCEPTION_FROM(className, parentName) \
    class className : public parentName { \
    public: \
        className() : parentName("") { } \
        explicit className(const String& reason) : parentName(reason) { } \
        ~className() override = default; \
    };

#define CUSTOM_EXCEPTION(className) CUSTOM_EXCEPTION_FROM(className, Exception)

CUSTOM_EXCEPTION(AssertionException)

#undef CUSTOM_EXCEPTION
#undef CUSTOM_EXCEPTION_FROM

}

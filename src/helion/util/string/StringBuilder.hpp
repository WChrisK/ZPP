#pragma once

#include <algorithm>
#include <sstream>
#include <string>
#include <type_traits>
#include "util/Defines.hpp"
#include "util/string/String.hpp"
#include "util/string/UpperString.hpp"

namespace Helion {

/**
 * Builds a string from dynamic input. Supports primitives and classes that
 * provide a toString() method.
 */
class StringBuilder {
    int precision = 5;
    std::string buffer;

public:
    /**
     * Appends the input provided to the internal buffer. This functions very
     * similarly to how iostreams work.
     *
     * It will convert everything into a string that is a primitive, and use
     * the precision value for floating point as either set by the caller or
     * a default value on object creation. If it is not a primitive, any class
     * that has a toString() method will have that method called and process
     * the result.
     *
     * @tparam T The type to stream in.
     *
     * @param t The value to stream in.
     *
     * @return A copy of the calling object, allowing for method chaining.
     */
    template <typename T>
    StringBuilder& operator<<(const T& t) {
        if constexpr (std::is_same_v<T, std::string> or std::is_same_v<T, char>) {
            buffer += t;
        } else if constexpr (std::is_same_v<T, uint8_t>) {
            buffer += std::to_string(uint32_t(t)); // Some print it as hex.
        } else if constexpr (std::is_floating_point_v<T>) {
            std::stringstream ss;
            ss.precision(precision);
            ss << t;
            buffer += ss.str();
        } else if constexpr (std::is_arithmetic_v<T>) {
            buffer += std::to_string(t);
        } else if constexpr (std::is_same_v<T, String> or std::is_same_v<T, UpperString>) {
            buffer += t.getStdStr();
        } else {
            buffer += t.toString().getStdStr();
        }

        return *this;
    }

    /**
     * Appends the C string to the internal buffer. See the operator<< overload
     * for more information.
     *
     * @param str The string to stream in. Must not be null.
     *
     * @return A copy of the calling object, allowing for method chaining.
     */
    StringBuilder& operator<<(const char* str) {
        buffer += str;
        return *this;
    }

    /**
     * Appends the element to the string builder.
     *
     * @tparam T The element type.
     *
     * @param t The element.
     *
     * @return Itself for chaining.
     */
    template <typename T>
    StringBuilder& operator()(const T& t) {
        operator<<(t);
        return *this;
    }

    /**
     * Appends a series of elements to the string builder.
     *
     * @tparam T The element type.
     * @tparam Args The remaining argument types.
     *
     * @param t The element.
     * @param args The remaining arguments to add recursively.
     *
     * @return Itself for chaining.
     */
    template <typename T, typename... Args>
    StringBuilder& operator()(const T& t, Args&&... args) {
        operator<<(t);
        return operator()(std::forward<Args>(args)...);
    }

    /**
     * Sets the precision to with which digits occur after the decimal place.
     *
     * @param precision The amount of digits after the decimal place. The value
     * provided is clamped so negative numbers become zero.
     */
    void setPrecision(const int precision) {
        this->precision = std::max(0, precision);
    }

    /**
     * Clears out all the characters and returns it to a default state.
     *
     * @return The current object for chaining.
     */
    StringBuilder& clear() {
        // Apparently this is ~40% faster than just assigning an empty string
        // according to the profiler!
        buffer.clear();
        buffer.shrink_to_fit();

        return *this;
    }

    /**
     * Will safely remove the last character if the buffer is not empty. This will
     * not crash or error if the buffer is empty.
     */
    void removeLastCharacterIfAny() {
        if (not buffer.empty())
            buffer.pop_back();
    }

    /**
     * Converts the internal representation to a string. This does not clear it or
     * mutate any state.
     *
     * @return A string of the current text inside.
     */
    String toString() const {
        return buffer;
    }

    /**
     * Gets the length of how many characters are in the buffer.
     *
     * @return The number of characters in the buffer.
     */
    int length() const {
        return int(buffer.length());
    }
};

}

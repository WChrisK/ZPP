#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace Helion {

/**
 * A global String class that has more functionality than the std::string one
 * and able to support UTF-8. All string creation should be done through this
 * class and not with std::string or const char *'s unless there is a specific
 * reason to do so.
 *
 * This also contains helper methods that are not currently present in the std
 * string class as of writing this.
 */
class String final {
    std::string str;

    template <typename T, typename... Args>
    void makeString(const T& t, Args&&... args) {
        if constexpr (std::is_same_v<T, String>) {
            str += t.str;
        } else if constexpr (std::is_same_v<T, std::string>) {
            str += t;
        } else if constexpr (std::is_same_v<T, char>) {
            str += std::string(1, t);
        }  else if constexpr (std::is_same_v<std::decay_t<std::remove_const_t<T>>, char*>) {
            str += std::string(t);
        } else if constexpr (std::is_arithmetic_v<T>) {
            str += std::to_string(t);
        } else if constexpr (std::is_convertible_v<T, std::string>) {
            str += std::string(t);
        } else if constexpr (std::is_pointer_v<T>) {
            std::ostringstream stream;
            const void* ptr = t;
            stream << ptr;
            const std::string temp = stream.str();
#ifdef _WIN32
            str += "0x" + temp;
#else
            str += temp;
#endif
        } else {
            str += t.toString().str;
        }

        if constexpr (sizeof...(Args) > 0)
            makeString(std::forward<Args>(args)...);
    }

public:
    static const int NO_INDEX = -1;

    static String fromPointer(const unsigned char* ptr, unsigned int length);
    static String fromEightCharEntry(const char* strData);

    template <typename... Args>
    static String from(Args&&... args) {
        String result;
        if constexpr (sizeof...(Args) > 0)
            result.makeString(std::forward<Args>(args)...);
        return result;
    }

    String() = default;
    String(char c);
    String(const char* s);
    String(const unsigned char* s);
    String(const std::string& s);
    String(const String& s) = default;
    String& operator=(const String& s) = default;
    String(String&& s) noexcept;
    String& operator=(String&& s) noexcept;
    ~String() = default;

    char operator[](int32_t index) const;
    bool operator==(const String& other) const;
    bool operator==(const std::string& other) const;
    bool operator==(const char* other) const;
    bool operator!=(const String& other) const;
    String operator+(char c) const;
    String operator+(const char* str) const;
    String operator+(const std::string& str) const;
    String operator+(const String& str) const;
    bool operator<(const String& str) const;
    bool operator<=(const String& str) const;
    bool operator>(const String& str) const;
    bool operator>=(const String& str) const;

    bool empty() const;
    const char* getChars() const;
    const std::string& getStdStr() const;
    int32_t length() const;
    uint32_t hashCode() const;
    String upper() const;
    String lower() const;
    int indexOf(char c) const;
    int lastIndexOf(char c) const;
    String substring(int32_t startIndex, int32_t pastEndIndex) const;
    String substringFrom(int32_t index) const;
    String substringTo(int32_t index) const;
    bool endsWith(const String& ending) const;
    String replace(char target, char replacer) const;
    String remove(char target) const;

    auto begin() const { return str.begin(); }
    auto end() const { return str.end(); }
    auto rbegin() const { return str.rbegin(); }
    auto rend() const { return str.rend(); }
    auto front() const { return str.front(); }
    auto back() const { return str.back(); }
};

inline std::ostream& operator<<(std::ostream& os, const String& str) {
    os << str.getChars();
    return os;
}

inline String operator+(const char* left, const String& right) {
    return String::from(left) + right;
}

inline String operator+(const std::string& left, const String& right) {
    return String::from(left) + right;
}

}

namespace std {
    template <>
    struct hash<Helion::String> {
        std::size_t operator()(const Helion::String& k) const {
            return k.hashCode();
        }
    };
}

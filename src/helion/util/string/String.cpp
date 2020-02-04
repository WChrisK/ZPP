#include <algorithm>
#include <cstring>
#include <locale>
#include <sstream>
#include "helion/util/Defines.hpp"
#include "helion/util/string/String.hpp"

namespace Helion {

String::String(const char c) :
    str(std::string(1, c)) {
}

String::String(const char* s) :
    str(s) {
}

String::String(const unsigned char* s) :
    str(reinterpret_cast<const char*>(s)) {
}

String::String(const std::string& s) :
    str(s) {
}

/**
 * Creates a string from an existing string.
 *
 * @param s The string to create it from.
 */
String::String(String&& s) noexcept {
    this->str = std::move(s.str);
}

/**
 * Assigns the string from a temporary.
 *
 * @param s The string to initialize it from.
 *
 * @return A reference to the current string.
 */
String& String::operator=(String&& s) noexcept {
    this->str = std::move(s.str);
    return *this;
}

/**
 * Creates a string from a pointer with a specified length. The result of using
 * a length greater than the ptr length is undefined.
 *
 * @param ptr The pointer to use. This should not be a null pointer.
 * @param length The length of the characters, not including '\0'.
 *
 * @return The converted string.
 */
String String::fromPointer(const unsigned char* ptr, unsigned int length) {
    std::string str;
    for (unsigned int i = 0; i < length; i++)
        str.append(1, ptr[i]);
    return str;
}

/**
 * A helper function that assumes strData has 8 characters (which may or may
 * not be '\0') and will create a string from them. This is a convenience
 * function that is used on lump entry data to safely get the name of the entry
 * whether its null terminated or not.
 *
 * @param strData A pointer to the string data. Must be at least 8 characters
 *                long or the results are undefined.
 *
 * @return The constructed string.
 */
String String::fromEightCharEntry(const char* strData) {
    std::string stringBuilder;
    for (int i = 0; i < 8; i++) {
        if (strData[i] == 0)
            break;
        stringBuilder += strData[i];
    }
    return String(stringBuilder);
}

/**
 * Gets the character at the index provided. Out of range indices are undefined
 * behavior.
 *
 * @param index The index of the character.
 *
 * @return The character at that index.
 */
char String::operator[](const int32_t index) const {
    return str[index];
}

/**
 * Checks if this string equals another.
 *
 * @param other The other string to check.
 *
 * @return True if they are equal, false otherwise.
 */
bool String::operator==(const String& other) const {
    if (this == &other)
        return true;
    if (str.length() != other.str.length())
        return false;
    return str == other.str;
}

/**
 * Checks if this string equals another.
 *
 * @param other The other string to check.
 *
 * @return True if they are equal, false otherwise.
 */
bool String::operator==(const std::string& other) const {
    return str == other;
}

/**
 * Checks if this string equals another. This is case sensitive.
 *
 * @param other The other string to check.
 *
 * @return True if they are equal, false otherwise.
 */
bool String::operator==(const char* other) const {
    return str == other;
}

/**
 * Checks if this string does not equal another. This is case sensitive.
 *
 * @param other The other string to check.
 *
 * @return True if they are equal, false otherwise.
 */
bool String::operator!=(const String& other) const {
    return not (this->operator==(other));
}

/**
 * Adds a character to the end of the current one and returns the new item.
 * This does not modify either string.
 *
 * @param c The char to concatenate.
 *
 * @return A new string of both joined into a new object.
 */
String String::operator+(char c) const {
    return str + String(c);
}

/**
 * Adds a string to the end of the current one and returns the new item. This
 * does not modify either string.
 *
 * @param str The string to concatenate.
 *
 * @return A new string of both joined into a new object.
 */
String String::operator+(const char* str) const {
    std::string internalStr = this->str;
    if (str != nullptr)
        internalStr += str;
    return String(internalStr);
}

/**
 * Adds a string to the end of the current one and returns the new item. This
 * does not modify either string.
 *
 * @param str The string to concatenate.
 *
 * @return A new string of both joined into a new object.
 */
String String::operator+(const std::string& str) const {
    std::string internalStr = this->str;
    internalStr += str;
    return String(internalStr);
}

/**
 * Adds a string to the end of the current one and returns the new item. This
 * does not modify either string.
 *
 * @param str The string to concatenate.
 *
 * @return A new string of both joined into a new object.
 */
String String::operator+(const String& str) const {
    std::string internalStr = this->str;
    internalStr += str.str;
    return String(this->str + str.str);
}

/**
 * Does a comparison on the string.
 *
 * @param str The string to compare against.
 *
 * @return True if it is less than, false otherwise.
 */
bool String::operator<(const String& str) const {
    return strcmp(getChars(), str.getChars()) < 0;
}

/**
 * Does a comparison on the string.
 *
 * @param str The string to compare against.
 *
 * @return True if it is less or equal to, false otherwise.
 */
bool String::operator<=(const String& str) const {
    return not this->operator>(str);
}

/**
 * Does a comparison on the string.
 *
 * @param str The string to compare against.
 *
 * @return True if it is greater than, false otherwise.
 */
bool String::operator>(const String& str) const {
    return str.operator<(*this);
}

/**
 * Does a comparison on the string.
 *
 * @param str The string to compare against.
 *
 * @return True if it is greater or equal to, false otherwise.
 */
bool String::operator>=(const String& str) const {
    return not this->operator<(str);
}

/**
 * Checks if the string is empty and has no characters.
 *
 * @return True if it's empty, false otherwise.
 */
bool String::empty() const {
    return length() == 0;
}

/**
 * Gets the characters in the C string format. This is unsafe to use if the
 * string is being modified since the underlying buffer could change.
 *
 * @return A pointer to the characters that make up this string.
 */
const char* String::getChars() const {
    return str.c_str();
}

/**
 * Gets the string in std::string format.
 *
 * @return The std::string format of the string.
 */
const std::string& String::getStdStr() const {
    return str;
}

/**
 * Gets the length of the string. Depending on the internal representation,
 * this will either be the number of characters (if ASCII), or how many bytes
 * if in some other form (like UTF-8).
 *
 * @return The length of the string.
 */
int32_t String::length() const {
    return int32_t(str.length());
}

/**
 * Hashes the string. The value is not stored, so this is generated on each run
 * of the algorithm.
 *
 * @return The hash of the string.
 */
 // Source: http://stackoverflow.com/questions/98153/whats-the-best-hashing-algorithm-to-use-on-a-stl-string-when-using-hash-map
uint32_t String::hashCode() const {
    unsigned int hash = 0;
    const char* s = str.c_str();
    unsigned int i = 0;
    char c;
    while ((c = s[i]) != 0) {
        hash = (hash * 101) + c;
        i++;
    }
    return hash;
}

/**
 * Converts the string to all upper case characters.
 *
 * @return A string of all upper case characters.
 */
String String::upper() const {
    std::string newString(str);
    std::transform(newString.begin(), newString.end(), newString.begin(), ::toupper);
    return newString;
}

/**
 * Converts the string to all lower case characters.
 *
 * @return A string of all lower case characters.
 */
String String::lower() const {
    std::string newString(str);
    std::transform(newString.begin(), newString.end(), newString.begin(), ::tolower);
    return newString;
}

/**
 * Gets the first index of the provided character. If none is found, it returns
 * String::NO_INDEX which indicates it is missing.
 *
 * @param c The character to look for.
 *
 * @return The index of the character, or String::NO_INDEX if it is missing.
 */
int String::indexOf(const char c) const {
    const char* chars = getChars();
    for (int i = 0; i < length(); i++)
        if (chars[i] == c)
            return i;
    return NO_INDEX;
}

/**
 * Gets the last index of the provided character. If none is found, it returns
 * String::NO_INDEX which indicates it is missing.
 *
 * @param c The character to look for.
 *
 * @return The index of the character, or String::NO_INDEX if it is missing.
 */
int String::lastIndexOf(const char c) const {
    const char* chars = getChars();
    for (int i = length() - 1; i >= 0; i--)
        if (chars[i] == c)
            return i;
    return NO_INDEX;
}

/**
 * Returns the substring from [start, end). This is undefined if any index is
 * out of range.
 *
 * @param startIndex The start index, where [0 <= startIndex < pastEndIndex].
 * @param endIndex The end index, where [0 <= startIndex < pastEndIndex].
 *
 * @return The substring from [start, end).
 */
String String::substring(const int32_t startIndex, const int32_t endIndex) const {
    return startIndex < endIndex ? String(str.substr(size_t(startIndex), size_t(endIndex - startIndex))) : "";
}

/**
 * Gets the substring from the provided index onwards. Using negative indices
 * is undefined behavior.
 *
 * @param index The index to get the substring from, and goes towards the end
 * of the string.
 *
 * @return The provided substring, or an empty string if it is out of range.
 *         Negative indices are undefined.
 */
String String::substringFrom(const int32_t index) const {
    return substring(index, length());
}

/**
 * Gets the substring from the beginning up to the provided index. Using
 * negative indices is undefined behavior.
 *
 * This means that it will go up to, but not including the index provided. Thus
 * a call with "abcd" with an index of 2 will return "ab".
 *
 * @param index The index of the end of the substring.
 *
 * @return The provided substring, or an empty string if it is out of range.
 *         Negative indices are undefined.
 */
String String::substringTo(const int32_t index) const {
    return substring(0, index);
}

/**
 * Checks if the string ends with the provided ending. It is safe to use an
 * ending that is longer than the target string, it will just return early as
 * false.
 *
 * @return True if it does, false if not.
 */
bool String::endsWith(const String& ending) const {
    if (ending.length() > length())
        return false;
    return std::equal(ending.str.rbegin(), ending.str.rend(), str.rbegin());
}

/**
 * Creates a copy of the current string where all instances of `target` are
 * replaced with `replacer`. If no matches are found, the returned string will
 * be identical to the current string (but a copy of it still).
 *
 * @param target The character to be replaced.
 * @param replacer The character to replace them with.
 *
 * @return A new string with the characters replaced.
 */
String String::replace(const char target, const char replacer) const {
    std::string copyStr = str;
    std::replace(copyStr.begin(), copyStr.end(), target, replacer);
    return copyStr;
}

/**
 * Removes the character provided from the string, and returns a new copy of a
 * string without the character.
 *
 * @param target The character to remove.
 *
 * @return A string without the character
 */
String String::remove(const char target) const {
    std::string s = str;
    auto it = std::remove(s.begin(), s.end(), target);
    s.erase(it, s.end());
    return s;
}

}

#pragma once

#include <cstdint>

// These are similar to ciso646's header values. We can't include them globally
// since some asm files will break if they run into `xor`.
#define and &&
#define or ||
#define not !

using byte = uint8_t;
using uint = unsigned int;

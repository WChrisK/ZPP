#pragma once

#include "helion/util/Defines.hpp"
#include "helion/util/string/String.hpp"

namespace Helion {

/**
 * A collection of version components which is easily comparable to other
 * versions.
 */
struct Version {
    const uint Major;
    const uint Minor;
    const uint Patch;
    
    constexpr explicit Version(const uint majorVersion, const uint minorVersion = 0, const uint patchVersion = 0) noexcept :
        Major(majorVersion),
        Minor(minorVersion),
        Patch(patchVersion) {
    }

    bool constexpr operator==(const Version& version) const noexcept {
        return Major == version.Major and Minor == version.Minor and Patch == version.Patch;
    }

    bool constexpr operator<(const Version& version) const noexcept {
        if (Major > version.Major)
            return false;
        if (Major < version.Major)
            return true;
        if (Minor > version.Minor)
            return false;
        if (Minor < version.Minor)
            return true;
        return Patch < version.Patch;
    }

    bool constexpr operator<=(const Version& version) const noexcept {
        return operator==(version) or operator<(version);
    }

    bool constexpr operator>(const Version& version) const noexcept {
        return not operator<=(version);
    }

    bool constexpr operator>=(const Version& version) const noexcept {
        return not operator<(version);
    }

    String toString() const {
        return String::from(Major, '.', Minor, '.', Patch);
    }
};

}

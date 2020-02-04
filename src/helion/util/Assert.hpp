#pragma once

#include "helion/util/Debug.hpp"
#include "helion/util/Exception.hpp"
#include "helion/util/string/StringBuilder.hpp"

#ifdef IS_DEBUG
#define HELION_USE_ASSERTIONS
#endif

namespace Helion::Assert {
    /**
     * Will always throw (assuming assertions are enabled).
     *
     * @tparam Args The arguments for the reasons.
     *
     * @param reasonArgs The reason for the exception.
     *
     * @throws AssertionException The exception when this is reached (assuming
     * assertion mode is enabled).
     */
    template <typename... Args>
    inline void fail([[maybe_unused]] Args&&... reasonArgs) {
#ifdef HELION_USE_ASSERTIONS
        StringBuilder stringBuilder;
        stringBuilder(std::forward<Args>(reasonArgs)...);
        throw AssertionException(stringBuilder.toString());
#endif
    }

    /**
     * A check for whether a precondition must hold before performing the rest
     * of the computations. This is intended to be used before a function due
     * to the function name.
     *
     * @tparam Args The arguments for the reasons.
     *
     * @param precondition The expression that should evaluate to true.
     * @param reasonArgs The reasons concatenated into a string for this.
     *
     * @throws AssertionException If assertions are enabled and precondition is
     * evaluated to be false.
     */
    template <typename... Args>
    inline void precondition([[maybe_unused]] const bool precondition, [[maybe_unused]] Args&&... reasonArgs) {
#ifdef HELION_USE_ASSERTIONS
        if (not precondition)
            fail(std::forward<Args>(reasonArgs)...);
#endif
    }

    /**
     * An invariant that must hold after some computations. This is intended to
     * be used in the middle of a function, or rather where a pre/postcondition
     * do not seem best to be used.
     *
     * @tparam Args The arguments for the reasons.
     *
     * @param invariant The expression that should evaluate to true.
     * @param reasonArgs The reasons concatenated into a string for this.
     *
     * @throws AssertionException If assertions are enabled and invariant is
     * evaluated to be false.
     */
    template <typename... Args>
    inline void invariant([[maybe_unused]] const bool invariant, [[maybe_unused]] Args&&... reasonArgs) {
#ifdef HELION_USE_ASSERTIONS
        if (not invariant)
            fail(std::forward<Args>(reasonArgs)...);
#endif
    }

    /**
     * A check for whether a postcondition must hold after completing a series
     * of computations. This is intended to be used at the end of a function or
     * before a return point due to the function name.
     *
     * @tparam Args The arguments for the reasons.
     *
     * @param postcondition The expression that should evaluate to true.
     * @param reasonArgs The reasons concatenated into a string for this.
     *
     * @throws AssertionException If assertions are enabled and postcondition
     * is evaluated to be false.
     */
    template <typename... Args>
    inline void postcondition([[maybe_unused]] const bool postcondition, [[maybe_unused]] Args&&... reasonArgs) {
#ifdef HELION_USE_ASSERTIONS
        if (not postcondition)
            fail(std::forward<Args>(reasonArgs)...);
#endif
    }
}

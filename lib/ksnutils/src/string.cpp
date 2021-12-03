#include <array.hpp>
#include <core/ksnucleus.hpp>
#include <string.hpp>

[[nodiscard]] uint16_t String::length() const
{
    // Cast this as a array, of the max string length
    const auto *string = reinterpret_cast<const Array<char, MAX_STRING_LENGTH> *>(raw());

    // Attempt to get the position of the null character
    auto answer = string->pos_of('\0');

    // Check if the null character was actually found
    if (!answer.valid)
    {
        // FIXME: What was I thinking?
        // Kill the system, we don't want invalid strings to be inserted
        ks_fission("Invalid string detected");
    }

    // Return the data for the answer
    return answer.data;
}

#include <array.hpp>
#include <core/ksnucleus.hpp>
#include <debug.hpp>
#include <string.hpp>

[[nodiscard]] uint16_t String::size() const
{
    // Cast this as a array, of the max string size
    const auto *string = reinterpret_cast<const Array<char, MAX_STRING_LENGTH> *>(raw());

    // Attempt to get the position of the null character
    auto answer = string->search([](auto search_term) { return search_term == '\0'; });

    // Check if the null character was actually found
    if (!answer.valid)
    {
        ks_fission("Invalid string detected");
    }

    // Return the data for the answer
    return answer.data;
}

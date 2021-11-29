#pragma once

#include <types.hpp>

#if defined(__CONFIG_KSNUCLEUS_DEBUG__)

template <typename T, typename... Ts> inline void print(T message, Ts... messages)
{
    print(message);
    print(messages...);
}

template <> inline void print<const char *>(const char *message)
{
    for (size_t i = 0, len = strlen(message); i < len; i++)
    {
    }
}

#else

#endif
#pragma once

#include <string.hpp>
#include <types.hpp>

#if defined(__CONFIG_KSNUCLEUS_DEBUG__)

template <typename T, typename... Ts> inline void debug(T msg, Ts... msgs)
{
    debug(msg);
    debug(msgs...);
}

template <> inline void debug<const char *>(const char *msg)
{
    String message(msg);

    for (uint32_t i = 0, len = message.size(); i < len; i++)
    {
    }
}

template <> inline void debug<uint32_t>(uint32_t msg)
{
}

#else

inline void debug(...)
{
}

#endif

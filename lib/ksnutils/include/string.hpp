#pragma once

#include <answer.hpp>
#include <types.hpp>

constexpr auto MAX_STRING_LENGTH = 1024;

class String
{
  private:
    const char *_internal_string;

  public:
    String() = default;
    constexpr String(const char *string) : _internal_string(string)
    {
    }

    constexpr const char *raw() const
    {
        return _internal_string;
    }

    [[nodiscard]] uint16_t length() const;
};

#pragma once

#include <answer.hpp>
#include <array.hpp>
#include <types.hpp>

constexpr auto MAX_STRING_LENGTH = 1024;

class String
{
  private:
    char *_internal_string;

  public:
    String() = default;
    constexpr String(char *string) : _internal_string(string)
    {
    }

    constexpr char *raw()
    {

        return _internal_string;
    }

    constexpr const char *raw() const
    {
        return _internal_string;
    }

    [[nodiscard]] uint16_t length() const;
};

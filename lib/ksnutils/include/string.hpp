#pragma once

#include <answer.hpp>
#include <types.hpp>

constexpr auto MAX_STRING_LENGTH = 1024;

class String
{
  private:
    const char *const _internal_string;

  public:
    constexpr String(const char *string) : _internal_string(string)
    {
    }

    constexpr const char *raw() const
    {
        return _internal_string;
    }

    [[nodiscard]] uint16_t size() const;
};

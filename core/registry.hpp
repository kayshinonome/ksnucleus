#pragma once
#include <table.hpp>
#include <types.hpp>

enum class Registry_Keys : uint16_t
{
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    SCREEN_DEPTH
};

class Registry : public Table<Registry_Keys, uint64_t, 3>
{
};

inline Registry global_registry{};

#pragma once
#include <array.hpp>
#include <array2d.hpp>
#include <atomic.hpp>
#include <types.hpp>

template <typename EVENT_DATA_TYPE, uint16_t EVENT_COUNT> class Event_Engine
{
  public:
    using Event_Handler = void (*)(uint16_t id, EVENT_DATA_TYPE data);

  private:
    Array2D<Atomic<Event_Handler>, EVENT_COUNT, 4> event_handlers{};

  public:
    bool fire(uint16_t id, EVENT_DATA_TYPE data)
    {
        // Ensure the ID isnt too large
        if (id >= EVENT_COUNT)
        {
            return false;
        }

        // Get the handlers that care about this interrupt
        auto event_handler_slice = event_handlers[id];

        for (uint16_t i = 0, len = event_handler_slice.length(); i < len; i++)
        {
            if (event_handler_slice[i] != nullptr)
            {
                event_handler_slice[i](id, data);
            }
        }

        return true;
    }

    bool add_event_handler(uint16_t id, Event_Handler event_handler)
    {
        // Ensure the ID isnt too large
        if (id >= EVENT_COUNT)
        {
            return false;
        }

        auto event_handler_slice = event_handlers[id];

        for (uint16_t i = 0, len = event_handler_slice.length(); i < len; i++)
        {
            if (event_handler_slice[i] == nullptr)
            {
                event_handler_slice[i] = event_handler;
                return true;
            }
        }
        return false;
    }
};
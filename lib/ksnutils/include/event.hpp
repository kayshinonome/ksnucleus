#pragma once
#include <array.hpp>
#include <array2d.hpp>
#include <types.hpp>

template <typename EVENT_DATA_TYPE, uint16_t EVENT_COUNT> class Event_Engine
{
    using Event_Handler = bool (*)(EVENT_DATA_TYPE data);

    /**
     * @brief The holder of the event
     * Its width is
     */
    Array2D<Event_Handler, EVENT_COUNT, 3> event_handlers{};

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
                event_handler_slice[i](data);
            }
        }

        return true;
    }
};
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

        for (uint16_t i = 0, len = event_handler_slice.size(); i < len; i++)
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
        auto result = event_handler_slice.search([](auto search_term) { return search_term == nullptr; });

        if (result.valid)
        {
            event_handler_slice[result.data] = event_handler;
            return true;
        }

        return false;
    }

    bool remove_event_handler(uint16_t id, Event_Handler event_handler)
    {
        // Ensure the ID isnt too large
        if (id >= EVENT_COUNT)
        {
            return false;
        }

        // Get the slice of the handlers that match
        auto event_handler_slice = event_handlers[id];

        // Do a search in the slice of events for the search term
        auto result =
            event_handler_slice.search([event_handler](auto search_term) { return event_handler == search_term; });

        // If was found, null out that function
        if (result.valid)
        {
            event_handler_slice[result.data] = nullptr;
            return true;
        }

        // The result was not found
        return false;
    }
};

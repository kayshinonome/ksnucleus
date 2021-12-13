#pragma once

#include <core/ksnucleus.hpp>
#include <types.hpp>

template <typename WRAPPED_TYPE> class Future
{
  private:
    WRAPPED_TYPE data;
    WRAPPED_TYPE (*callback)() = nullptr;
    bool has_been_called_yet = false;

    WRAPPED_TYPE &fetch_data()
    {
        if (!has_been_called_yet)
        {
            if (callback == nullptr)
            {
                ks_fission("Future missing its callback");
            }
            data = callback();
        }
        return data;
    }

  public:
    explicit Future(WRAPPED_TYPE (*func)()) : callback(func)
    {
    }

    operator WRAPPED_TYPE() const
    {
        return fetch_data();
    }

    operator WRAPPED_TYPE &()
    {
        return fetch_data();
    }
};

#pragma once
#include <answer.hpp>
#include <array.hpp>

template <typename KEY_TYPE, typename DATA_TYPE, uint32_t SIZE> class Table
{
  private:
    class Key_Data_Pair
    {
      public:
        bool been_set = false;
        KEY_TYPE key;
        DATA_TYPE data;
    };

  public:
    Array<Key_Data_Pair, SIZE> _internal_data;

    Answer<DATA_TYPE> get(KEY_TYPE key)
    {
        for (uint32_t x = 0; x < _internal_data.length(); x++)
        {
            if (_internal_data[x].been_set && _internal_data[x].key == key)
            {
                return {.data = _internal_data[x].data, .valid = true};
            }
        }
        return {};
    }

    bool set(KEY_TYPE key, DATA_TYPE data)
    {
        for (uint32_t x = 0; x < _internal_data.length(); x++)
        {
            if (_internal_data[x].been_set && _internal_data[x].key == key)
            {
                _internal_data[x].data = data;
                return true;
            }
        }
        for (uint32_t x = 0; x < _internal_data.length(); x++)
        {
            if (!_internal_data[x].been_set)
            {
                _internal_data[x].data = data;
                _internal_data[x].been_set = true;
                _internal_data[x].key = key;
                return true;
            }
        }
        return false;
    }
};

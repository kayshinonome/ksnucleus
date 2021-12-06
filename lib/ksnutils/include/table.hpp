#pragma once
#include <answer.hpp>
#include <array.hpp>
#include <math.hpp>

// NOTE: Please, Please, this class's operations are fairly intensive. Only use it when you need it.

/**
 * @brief A hash based table (crc32)
 *
 * @tparam KEY_TYPE
 * @tparam DATA_TYPE
 * @tparam SIZE
 */
template <typename KEY_TYPE, typename DATA_TYPE, uint32_t SIZE> class Table
{
  private:
    Array<uint32_t, SIZE> _internal_keys;
    Array<DATA_TYPE, SIZE> _internal_data;
    uint32_t pos_in_table = 0;

  public:
    /**
     * @brief Get a value, if it exists
     *
     * @param key
     * @return Answer<DATA_TYPE>
     */
    constexpr Answer<DATA_TYPE> get(KEY_TYPE key)
    {
        // Check if the crc has been seen before
        auto answer = _internal_keys.pos_of(crc32(key));

        if (!answer.valid)
        {
            // Return nothing.
            return {};
        }

        return {.valid = true, .data = _internal_data[answer.data]};
    }

    /**
     * @brief Set a value
     *
     * @param key
     * @param data
     * @return true
     * @return false
     */
    constexpr bool set(KEY_TYPE key, DATA_TYPE data)
    {
        // Check if the crc has been seen before
        auto crc = crc32(key);
        auto answer = _internal_keys.pos_of(crc);

        if (!answer.valid)
        {
            // Key was not seen before

            // If the table is already full, leave
            if (pos_in_table >= _internal_keys.size())
            {
                return false;
            }

            // Set the data and add to the counter
            _internal_keys[pos_in_table] = crc;
            _internal_data[pos_in_table++] = data;
            return true;
        }

        _internal_data[answer.data] = data;
        return true;
    }
};

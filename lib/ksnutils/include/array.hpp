#pragma once

#include <types.hpp>
#include <utils.hpp>

/**
 * @brief A safe array type that represents as many arrays as possible in ksnucleus
 *
 * @tparam ARRAY_TYPE
 * @tparam SIZE
 */
template <typename ARRAY_TYPE, size_t SIZE> class Array
{
    /**
     * @brief Internal array
     *
     */
  public:
    /**
     * @brief Internal array to store data
     *
     */
    ARRAY_TYPE _internal_buffer[SIZE];

    /**
     * @brief Read a element
     *
     * @param index
     * @return ARRAY_TYPE
     */
    ARRAY_TYPE operator[](size_t index) const
    {
        if (index >= SIZE)
        {
            while (true)
            {
            }
        }

        return raw()[index];
    }

    /**
     * @brief Write to a element
     *
     * @param index
     * @return ARRAY_TYPE&
     */
    ARRAY_TYPE &operator[](size_t index)
    {
        if (index >= SIZE)
        {
            while (true)
            {
            }
        }

        return raw()[index];
    }

    /**
     * @brief Get the length of the array, calculated at compile time
     *
     * @return constexpr size_t
     */
    [[nodiscard]] constexpr size_t length() const
    {
        return SIZE;
    }

    /**
     * @brief Get the raw, underlying array
     *
     * @return ARRAY_TYPE*
     */
    constexpr ARRAY_TYPE *raw()
    {
        return _internal_buffer;
    }

    /**
     * @brief Get the raw, underlying const array
     *
     * @return ARRAY_TYPE*
     */
    constexpr const ARRAY_TYPE *raw() const
    {
        return _internal_buffer;
    }

    /**
     * @brief Sort the array (Bubble sort for now)
     *
     * @param cmp
     */
    void sort(bool (*cmp)(const ARRAY_TYPE &, const ARRAY_TYPE &))
    {
        auto raw_array = raw();
        auto swapped = false;

        for (size_t x = 0, len = length(); x < len - 1; x++)
        {
            swapped = false;
            for (size_t y = 0; y < len - x - 2; y++)
            {
                if (cmp(raw_array[y], raw_array[y + 1]))
                {
                    auto tmp = raw_array[y];
                    raw_array[y] = raw_array[y + 1];
                    raw_array[y + 1] = tmp;
                    swapped = true;
                }
            }

            if (!swapped)
            {
                break;
            }
        }
    }

    /**
     * @brief Copy contructor
     *
     * @param data
     * @return ksArray&
     */
    Array &operator=(const Array &data)
    {
        if (this != reinterpret_cast<const Array<ARRAY_TYPE, SIZE> *>(data))
        {
            from(data.raw());
        }
        return *this;
    }

    /**
     * @brief Copy contructor (for raw ARRAY_TYPE)
     *
     * @param data
     * @return ksArray&
     */
    Array &operator=(const ARRAY_TYPE data[])
    {
        if (this != reinterpret_cast<const Array<ARRAY_TYPE, SIZE> *>(data))
        {
            from(data);
        }
        return *this;
    }

    /**
     * @brief Function to check if equals
     *
     * @param data
     * @return bool
     */
    bool operator==(const Array &data)
    {
        return compare_memory(raw(), data.raw(), SIZE);
    }

    /**
     * @brief Inequality operator
     *
     * @param data
     * @return bool
     */
    bool operator!=(const Array &data) const
    {
        return !compare_memory(raw(), data.raw(), SIZE);
    }

    /**
     * @brief Fill this array with elements from a raw array passed in
     *
     * @param data
     */
    void from(const ARRAY_TYPE data[])
    {
        copy_memory(data, raw(), length());
    }
};

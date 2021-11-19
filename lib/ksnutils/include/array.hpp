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
  public:
    ARRAY_TYPE _internal_buffer[SIZE];

    /**
     * @brief Read a element
     *
     * @param index
     * @return ARRAY_TYPE
     */
    constexpr ARRAY_TYPE operator[](size_t index) const
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
    constexpr ARRAY_TYPE &operator[](size_t index)
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
     * @brief Returns the length at runtime
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
        auto swapped = false;
        auto &array = (*this);

        for (size_t x = 0, len = length(); x < len - 1; x++)
        {
            swapped = false;
            for (size_t y = 0; y < len - x - 2; y++)
            {
                if (cmp(array[y], array[y + 1]))
                {
                    auto tmp = array[y];
                    array[y] = array[y + 1];
                    array[y + 1] = tmp;
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
        if (this != &data)
        {
            copy_memory(data.raw(), raw(), length());
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
            copy_memory(data, raw(), length());
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
     * @brief Get the smallest value in the array (calculated using <)
     *
     * @return ARRAY_TYPE
     */
    ARRAY_TYPE smallest() const
    {
        ARRAY_TYPE possible_element = (*this)[0];

        if (length() == 1)
        {
            return possible_element;
        }

        for (size_t x = 0; x < length(); x++)
        {
            if ((*this)[x] < possible_element)
            {
                possible_element = (*this)[x];
            }
        }

        return possible_element;
    }

    /**
     * @brief Get the biggest value in the array (calculated using >)
     *
     * @return ARRAY_TYPE
     */
    ARRAY_TYPE largest() const
    {
        ARRAY_TYPE possible_element = (*this)[0];

        if (length() == 1)
        {
            return possible_element;
        }

        for (size_t x = 0; x < length(); x++)
        {
            if ((*this)[x] > possible_element)
            {
                possible_element = (*this)[x];
            }
        }

        return possible_element;
    }
};

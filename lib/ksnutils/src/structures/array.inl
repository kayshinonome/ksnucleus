#pragma once

#include <utils.hpp>

template <typename ARRAY_TYPE, size_t SIZE> [[nodiscard]] constexpr size_t Array<ARRAY_TYPE, SIZE>::length() const
{
    return SIZE;
}

template <typename ARRAY_TYPE, size_t SIZE>
[[nodiscard]] ARRAY_TYPE Array<ARRAY_TYPE, SIZE>::operator[](size_t index) const
{
    if (index > SIZE)
    {
        while (true)
        {
        }
    }

    return raw()[index];
}

template <typename ARRAY_TYPE, size_t SIZE> ARRAY_TYPE &Array<ARRAY_TYPE, SIZE>::operator[](size_t index)
{
    if (index > SIZE)
    {
        while (true)
        {
        }
    }

    return raw()[index];
}

template <typename ARRAY_TYPE, size_t SIZE> constexpr ARRAY_TYPE *Array<ARRAY_TYPE, SIZE>::raw()
{
    return _internal_buffer;
}

template <typename ARRAY_TYPE, size_t SIZE> constexpr const ARRAY_TYPE *Array<ARRAY_TYPE, SIZE>::raw() const
{
    return _internal_buffer;
}

template <typename ARRAY_TYPE, size_t SIZE>
void Array<ARRAY_TYPE, SIZE>::sort(bool (*cmp)(const ARRAY_TYPE &, const ARRAY_TYPE &))
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

template <typename ARRAY_TYPE, size_t SIZE>
Array<ARRAY_TYPE, SIZE> &Array<ARRAY_TYPE, SIZE>::operator=(const Array &data)
{
    if (this != reinterpret_cast<const Array<ARRAY_TYPE, SIZE> *>(data))
    {
        from(data.raw());
    }
    return *this;
}

template <typename ARRAY_TYPE, size_t SIZE>
Array<ARRAY_TYPE, SIZE> &Array<ARRAY_TYPE, SIZE>::operator=(const ARRAY_TYPE data[])
{
    if (this != reinterpret_cast<const Array<ARRAY_TYPE, SIZE> *>(data))
    {
        from(data);
    }
    return *this;
}

template <typename ARRAY_TYPE, size_t SIZE> bool Array<ARRAY_TYPE, SIZE>::operator==(const Array &data)
{
    // If the pointers are the same they are equal
    if (data.raw() == raw())
    {
        return true;
    }

    return memcmp(data.raw(), raw(), length() * sizeof(ARRAY_TYPE)) == 0;
}

template <typename ARRAY_TYPE, size_t SIZE> bool Array<ARRAY_TYPE, SIZE>::operator!=(const Array &data)
{
    auto data_internal_array = data.raw();
    auto internal_array = raw();

    // If the pointers are the same they are equal
    if (data_internal_array == internal_array)
    {
        return false;
    }

    return memcmp(data_internal_array, internal_array, length() * sizeof(ARRAY_TYPE)) != 0;
}

template <typename ARRAY_TYPE, size_t SIZE> void Array<ARRAY_TYPE, SIZE>::from(const ARRAY_TYPE data[])
{
    copy_memory(data, raw(), length());
}
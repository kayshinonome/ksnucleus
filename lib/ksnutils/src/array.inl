#pragma once
#include <answer.hpp>
#include <array.hpp>
#include <core/ksnucleus.hpp>
#include <types.hpp>

template <typename ARRAY_TYPE, uint32_t SIZE>
constexpr ARRAY_TYPE Array<ARRAY_TYPE, SIZE>::operator[](uint32_t index) const
{
    if (index >= size())
    {
        ks_fission("Buffer overflow detected");
    }

    return raw()[index];
}

template <typename ARRAY_TYPE, uint32_t SIZE> constexpr ARRAY_TYPE &Array<ARRAY_TYPE, SIZE>::operator[](uint32_t index)
{
    if (index >= size())
    {
        ks_fission("Buffer overflow detected");
    }

    return raw()[index];
}

template <typename ARRAY_TYPE, uint32_t SIZE> [[nodiscard]] constexpr uint32_t Array<ARRAY_TYPE, SIZE>::size()
{
    return SIZE;
}

template <typename ARRAY_TYPE, uint32_t SIZE> constexpr ARRAY_TYPE *Array<ARRAY_TYPE, SIZE>::raw()
{
    return _internal_buffer;
}

template <typename ARRAY_TYPE, uint32_t SIZE> constexpr const ARRAY_TYPE *Array<ARRAY_TYPE, SIZE>::raw() const
{
    return _internal_buffer;
}

template <typename ARRAY_TYPE, uint32_t SIZE>
Array<ARRAY_TYPE, SIZE> &Array<ARRAY_TYPE, SIZE>::sort(bool (*cmp)(const ARRAY_TYPE &, const ARRAY_TYPE &))
{
    auto swapped = false;
    auto &array = (*this);

    for (size_t x = 0, len = size(); x < len - 1; x++)
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
    return *this;
}

template <typename ARRAY_TYPE, uint32_t SIZE>
Array<ARRAY_TYPE, SIZE> &Array<ARRAY_TYPE, SIZE>::operator=(const ARRAY_TYPE data[])
{
    this->copy_into(data);
    return *this;
}

template <typename ARRAY_TYPE, uint32_t SIZE>
bool Array<ARRAY_TYPE, SIZE>::operator==(const Array<ARRAY_TYPE, SIZE> &data) const
{
    return compare_memory(raw(), data.raw(), SIZE);
}

template <typename ARRAY_TYPE, uint32_t SIZE> [[nodiscard]] constexpr size_t Array<ARRAY_TYPE, SIZE>::sizeof_type()
{
    return sizeof(ARRAY_TYPE);
}

template <typename ARRAY_TYPE, uint32_t SIZE>
Array<ARRAY_TYPE, SIZE> &Array<ARRAY_TYPE, SIZE>::copy_into(const ARRAY_TYPE data[])
{
    if (this != reinterpret_cast<const Array<ARRAY_TYPE, SIZE> *>(data))
    {
        copy_memory(data, raw(), size());
    }
    return *this;
}

template <typename ARRAY_TYPE, uint32_t SIZE>
template <typename T>
constexpr Answer<uint32_t> Array<ARRAY_TYPE, SIZE>::search(T search_func) const
{
    // NOTE: I cannot specify the possible type on function so I will ensure that the program writer can figure out that
    // you need to pass a pointer to a function that takes one argument of ARRAY_TYPE. The reason this is done like this
    // is so you can pass in pointers to capturing lambdas, which is needed for most pratical uses of this function
    // Please note that type safety is still enforced at compile time however

    Answer<uint32_t> answer = {.valid = false, .data = 0};
    for (size_t i = 0, len = size(); i < len; i++)
    {
        if (search_func((*this)[i]))
        {
            answer.valid = true;
            answer.data = i;
            break;
        }
    }
    return answer;
}

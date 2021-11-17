#pragma once

#include <types.hpp>

template <typename T> class Atomic
{
  private:
    T _internal_data;

  public:
    Atomic() = default;

    Atomic(const T &data)
    {
        // NOTE: We shouldn't have to cast away constness, but we have no choice
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        __atomic_store(&_internal_data, const_cast<T *>(&data), __ATOMIC_SEQ_CST);
    }

    operator T()
    {
        T tmp;
        __atomic_load(&_internal_data, &tmp, __ATOMIC_SEQ_CST);
        return tmp;
    }

    Atomic operator++()
    {
        __atomic_fetch_add(&_internal_data, 1, __ATOMIC_SEQ_CST);
        return *this;
    }

    Atomic operator++(int data) &
    {
        __atomic_fetch_add(&_internal_data, 1, __ATOMIC_SEQ_CST);
        return *this;
    }

    Atomic operator--()
    {
        __atomic_fetch_sub(&_internal_data, 1, __ATOMIC_SEQ_CST);
        return *this;
    }

    Atomic operator--(int data) &
    {
        __atomic_fetch_sub(&_internal_data, 1, __ATOMIC_SEQ_CST);
        return *this;
    }

    Atomic &operator=(const Atomic &data)
    {
        if (&data == this)
        {
            return *this;
        }

        // NOTE: We shouldn't have to cast away constness, but we have no choice
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        __atomic_store(&_internal_data, const_cast<T *>(&data._internal_data), __ATOMIC_SEQ_CST);
        return *this;
    }

    Atomic operator+=(const T &data)
    {
        __atomic_fetch_add(&_internal_data, data, __ATOMIC_SEQ_CST);
        return *this;
    }

    Atomic operator-=(const T &data)
    {
        __atomic_fetch_sub(&_internal_data, data, __ATOMIC_SEQ_CST);
        return *this;
    }

    Atomic operator^=(const T &data)
    {
        __atomic_fetch_xor(&_internal_data, data, __ATOMIC_SEQ_CST);
        return *this;
    }

    // We have to set the alignment otherwise we will get a massive penalty from the atomic operations
} __attribute__((aligned(sizeof(T))));

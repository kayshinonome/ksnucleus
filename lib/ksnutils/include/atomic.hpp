#pragma once

#include <types.hpp>

template <typename T> class Atomic
{
  private:
    T _internal_data;

  public:
    operator T()
    {
        T tmp;
        __atomic_load(&_internal_data, &tmp, __ATOMIC_SEQ_CST);
        return tmp;
    }

    Atomic operator++()
    {
        __atomic_add_fetch(&_internal_data, 1, __ATOMIC_SEQ_CST);
        return *this;
    }

    Atomic operator++(int data) &
    {
        __atomic_add_fetch(&_internal_data, 1, __ATOMIC_SEQ_CST);
        return *this;
    }

    Atomic operator--()
    {
        __atomic_sub_fetch(&_internal_data, 1, __ATOMIC_SEQ_CST);
        return *this;
    }

    Atomic operator--(int data) &
    {
        __atomic_sub_fetch(&_internal_data, 1, __ATOMIC_SEQ_CST);
        return *this;
    }
};
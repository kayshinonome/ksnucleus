#pragma once
#include <utils.hpp>

template <typename T> Future<T>::Future(T (*callback)(Future<T> &future))
{
}

template <typename T> T Future<T>::get()
{
    while (callback != nullptr)
    {
        return callback(this);
    }
}
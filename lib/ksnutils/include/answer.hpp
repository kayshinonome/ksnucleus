/**
 * @file answer.hpp
 * @author Kay Shinonome (kayshinonome@protonmail.com)
 * @brief Class providing a answer interfaces for sync functions that could fail
 *
 */
#pragma once

#include <types.hpp>

template <typename T> class Answer
{
  public:
    bool valid;
    T data;
};
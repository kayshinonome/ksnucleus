/**
 * @file answer.hpp
 * @author Kay Shinonome (kayshinonome@protonmail.com)
 * @brief Class providing a answer interfaces for sync functions that could fail
 * @version 0.1
 * @date 2021-11-29
 *
 * @copyright Copyright (c) 2021
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
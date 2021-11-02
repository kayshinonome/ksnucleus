#pragma once

#if defined(__SIZE_TYPE__)
using size_t = __SIZE_TYPE__;
#endif

#if defined(__PTRDIFF_TYPE__)
using ptrdiff_t = __PTRDIFF_TYPE__;
#endif

#if defined(__UINTPTR_TYPE__)
using uintptr_t = __UINTPTR_TYPE__;
#endif

#if defined(__INT8_TYPE__)
using int8_t = __INT8_TYPE__;
#endif

#if defined(__INT16_TYPE__)
using int16_t = __INT16_TYPE__;
#endif

#if defined(__INT32_TYPE__)
using int32_t = __INT32_TYPE__;
#endif

#if defined(__INT64_TYPE__)
using int64_t = __INT64_TYPE__;
#endif

#if defined(__UINT8_TYPE__)
using uint8_t = __UINT8_TYPE__;
#endif

#if defined(__UINT16_TYPE__)
using uint16_t = __UINT16_TYPE__;
#endif

#if defined(__UINT32_TYPE__)
using uint32_t = __UINT32_TYPE__;
#endif

#if defined(__UINT64_TYPE__)
using uint64_t = __UINT64_TYPE__;
#endif

constexpr auto M_PI = 3.14159265358979311600;

/**
 * @brief memcpy that copies using native words sizes when possible
 *
 * @tparam T The type of the block to be copied
 * @param src Source data
 * @param dest Destination data
 * @param count Number of blocks to copy
 */
template <typename T> void copy_memory(const T src[], T dest[], size_t count);

/**
 * @brief memset that copies using native words sizes when possible
 *
 * @tparam T
 * @param dest
 * @param value
 * @param count
 */
template <typename T> void set_memory(T dest[], uint8_t value, size_t count);

/**
 * @brief Get the absolute value of a function
 *
 * @tparam T
 * @param x
 * @return T
 */
template <typename T> T abs(T x);

/**
 * @brief Get a approximate for sin
 *
 * @tparam T
 * @param x
 * @return T
 */
template <typename T> T sin(T x);

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
    ARRAY_TYPE operator[](size_t index) const;

    /**
     * @brief Write to a element
     *
     * @param index
     * @return ARRAY_TYPE&
     */
    ARRAY_TYPE &operator[](size_t index);

    /**
     * @brief Get the length of the array, calculated at compile time
     *
     * @return constexpr size_t
     */
    [[nodiscard]] constexpr size_t length() const;

    /**
     * @brief Get the raw, underlying array
     *
     * @return ARRAY_TYPE*
     */
    constexpr ARRAY_TYPE *raw();

    /**
     * @brief Get the raw, underlying const array
     *
     * @return ARRAY_TYPE*
     */
    constexpr const ARRAY_TYPE *raw() const;

    /**
     * @brief Sort the array (Bubble sort for now)
     *
     * @param cmp
     */
    void sort(bool (*cmp)(const ARRAY_TYPE &, const ARRAY_TYPE &));

    /**
     * @brief Copy contructor
     *
     * @param data
     * @return ksArray&
     */
    Array &operator=(const Array &data);

    /**
     * @brief Copy contructor (for raw ARRAY_TYPE)
     *
     * @param data
     * @return ksArray&
     */
    Array &operator=(const ARRAY_TYPE data[]);

    /**
     * @brief Function to check if equals
     *
     * @param data
     * @return bool
     */
    bool operator==(const Array &data);

    /**
     * @brief Inequality operator
     *
     * @param data
     * @return bool
     */
    bool operator!=(const Array &data);

    /**
     * @brief Fill this array with elements from a raw array passed in
     *
     * @param data
     */
    void from(const ARRAY_TYPE data[]);
};

template <typename ARRAY_TYPE, size_t WIDTH, size_t HEIGHT>
class Array2D : public Array<Array<ARRAY_TYPE, HEIGHT>, WIDTH>
{
  public:
    /**
     * @brief Return this as a flat array
     *
     * @return Array<ARRAY_TYPE, WIDTH * HEIGHT>&
     */
    Array<ARRAY_TYPE, WIDTH * HEIGHT> &as_flat_array();

    /**
     * @brief Return this as a flat const array
     *
     * @return const Array<ARRAY_TYPE, WIDTH * HEIGHT>&
     */
    const Array<ARRAY_TYPE, WIDTH * HEIGHT> &as_flat_array() const;

    /**
     * @brief Get the width of the array, calculated at compile time
     *
     * @return constexpr int
     */
    [[nodiscard]] constexpr size_t width() const;

    /**
     * @brief Get the height of the array, calculated at compile time
     *
     * @return constexpr int
     */
    [[nodiscard]] constexpr size_t height() const;
};

template <typename T> class Future
{
    T (*callback)(Future<T> &future);

  public:
    explicit Future(T (*callback)(Future<T> &future));

    T get();
};

#include <lib/ksnutils/src/math/abs.inl>
#include <lib/ksnutils/src/math/sin.inl>
#include <lib/ksnutils/src/memops/copy_memory.inl>
#include <lib/ksnutils/src/memops/set_memory.inl>
#include <lib/ksnutils/src/structures/array.inl>
#include <lib/ksnutils/src/structures/array2d.inl>
#include <lib/ksnutils/src/structures/future.inl>

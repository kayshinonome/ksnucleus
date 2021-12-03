#pragma once

#include <answer.hpp>
#include <types.hpp>
#include <utils.hpp>

/**
 * @brief A safe array type that represents as many arrays as possible in ksnucleus
 *
 * @tparam ARRAY_TYPE
 * @tparam SIZE
 */
template <typename ARRAY_TYPE, uint32_t SIZE> class Array
{
  public:
    ARRAY_TYPE _internal_buffer[SIZE];

    /**
     * @brief Read a element
     *
     * @param index
     * @return ARRAY_TYPE
     */
    constexpr ARRAY_TYPE operator[](uint32_t index) const;

    /**
     * @brief Write to a element
     *
     * @param index
     * @return ARRAY_TYPE&
     */
    constexpr ARRAY_TYPE &operator[](uint32_t index);

    /**
     * @brief Returns the length at runtime
     *
     * @return constexpr size_t
     */
    [[nodiscard]] constexpr static uint32_t length();

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
    Array &sort(bool (*cmp)(const ARRAY_TYPE &, const ARRAY_TYPE &));

    /**
     * @brief Copy contructor (for raw ARRAY_TYPE)
     *
     * @param data
     * @return Array&
     */
    Array &operator=(const ARRAY_TYPE data[]);

    /**
     * @brief Function to check if equals
     *
     * @param data
     * @return bool
     */
    bool operator==(const Array &data) const;

    /**
     * @brief Get the size of the underlying array type
     *
     * @return constexpr size_t
     */
    [[nodiscard]] constexpr static size_t sizeof_type();

    /**
     * @brief Copy data into the array
     *
     * @param data
     * @return Array&
     */
    Array &copy_into(const ARRAY_TYPE data[]);

    /**
     * @brief Get the position of the first element matching search
     *
     * @param search Element to search for
     * @return constexpr Answer<uint32_t>
     */
    constexpr Answer<uint32_t> pos_of(ARRAY_TYPE search) const;
};

#include <lib/ksnutils/src/array.inl>
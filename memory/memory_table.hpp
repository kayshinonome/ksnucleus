#include <array.hpp>
#include <permission.hpp>
#include <types.hpp>

class Memory_Table_Entry
{
  public:
    /**
     * @brief The start of the memory segment
     *
     */
    void *memory;

    /**
     * @brief Length of the memory block
     *
     */
    size_t block_length;

    /**
     * @brief Check if the block is unallocated
     *
     */
    bool is_reserved;

    /**
     * @brief Permissions for the memory
     *
     */
    Permissions permissions;
};

template <uint32_t SIZE> class Memory_Table : public Array<Memory_Table_Entry, SIZE>
{
};

constinit inline Memory_Table<0xff> allocated_memory_table{};

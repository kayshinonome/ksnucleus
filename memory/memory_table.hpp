#include <array.hpp>
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
};

class Memory_Table : public Array<Memory_Table_Entry, 0xff>
{
};

inline Memory_Table memory_table;
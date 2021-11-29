#include <arch/x86/gdt.hpp>
#include <types.hpp>
#include <utils.hpp>

/**
 * @brief Pointer to the GDT
 *
 */
class GDT_Ptr
{
  private:
    const uint16_t limit = sizeof(GDT) - 1;
    const GDT *base;

  public:
    explicit GDT_Ptr(const GDT *gdt) : base(gdt)
    {
    }

} __attribute__((packed));

extern "C"
{
    void flush_gdt(GDT_Ptr *gdt_ptr);
}

/**
 * @brief Init and load the gdt
 *
 */
bool GDT::init()
{

    constexpr uint16_t GDT_CODE_PL0 =
        SEG_TYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | SEG_PRIV(0) | SEG_CODE_EXRD;

    constexpr uint16_t GDT_DATA_PL0 =
        SEG_TYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | SEG_PRIV(0) | SEG_DATA_RDWR;

    constexpr uint16_t GDT_CODE_PL3 =
        SEG_TYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | SEG_PRIV(3) | SEG_CODE_EXRD;

    constexpr uint16_t GDT_DATA_PL3 =
        SEG_TYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | SEG_PRIV(3) | SEG_DATA_RDWR;

    const GDT gdt{{GDT::get_descriptor(0, 0, 0), GDT::get_descriptor(0, 0x000fffff, GDT_CODE_PL0),
                   GDT::get_descriptor(0, 0x000fffff, GDT_DATA_PL0), GDT::get_descriptor(0, 0x000fffff, GDT_CODE_PL3),
                   GDT::get_descriptor(0, 0x000fffff, GDT_DATA_PL3)}};

    GDT_Ptr gdt_ptr(&gdt);

    /**
     * @brief Generated GDT is
     *  [0] 0x0000000000000000
     *  [1] 0x00CF9A000000FFFF
     *  [2] 0x00CF92000000FFFF
     *  [3] 0x00CFFA000000FFFF
     *  [4] 0x00CFF2000000FFFF
     *
     * In order to read the GDT in GDB, run
     * p/x (uint64_t[5])gdt
     *
     */

    flush_gdt(&gdt_ptr);
    return true;
}
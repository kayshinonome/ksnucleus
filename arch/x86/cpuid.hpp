#pragma once
#include <array.hpp>
#include <string.hpp>
#include <types.hpp>

namespace cpuid
{

    enum class CPU_Vendor : uint8_t
    {
        UNKNOWN,
        AMD,
        INTEL,
        VIA,
        TRANSMETA,
        CYRIX,
        CENTAUR,
        NEXGEN,
        UMC,
        SIS,
        NSC,
        RISE,
        VORTEX,
        AO486,
        ZHAOXIN,
        HYGON,
        ELBRUS,
        QEMU,
        KVM,
        VMWARE,
        VIRTUALBOX,
        XEN,
        HYPERV,
        PARALLELS,
        BHYVE,
        QNX
    };

// We need to check for this in i386 mode
#if defined(__i386__)

    /**
     * @brief Check for cpuid support
     *
     */
    extern "C" bool check_support();

#else

    extern "C" constexpr bool check_support()
    {
        return true;
    }

#endif

    void cpuid(uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx);

    /**
     * @brief Get the highest function parameter of cpuid
     *
     * @return uint32_t
     */
    uint32_t highest_function_parameter();

    /**
     * @brief Get the manufacturer_id
     *
     * @param buffer
     */
    void get_vendor_id(Array<char, 12> &buffer);

    CPU_Vendor get_vendor();

} // namespace cpuid
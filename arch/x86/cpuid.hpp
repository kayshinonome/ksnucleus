#pragma once
#include <array.hpp>
#include <string.hpp>
#include <types.hpp>

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
extern "C" bool cpuid_check_support();

#else

extern "C" constexpr bool cpuid_check_support()
{
    return true;
}

#endif

void cpuid(size_t *eax, size_t *ebx, size_t *ecx, size_t *edx);

/**
 * @brief Get the highest function parameter of cpuid
 *
 * @return uint32_t
 */
uint32_t cpuid_highest_function_parameter();

/**
 * @brief Get the manufacturer_id
 *
 * @param buffer
 */
void cpuid_get_vendor_id(Array<char, 12> &buffer);

CPU_Vendor cpuid_get_vendor();
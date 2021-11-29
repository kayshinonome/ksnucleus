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

class CPU_String_Couple
{
  public:
    String cpu_vendor_string;
    CPU_Vendor cpu_vendor;
};

const Array<CPU_String_Couple, 29> cpu_vendor_string_table{
    {{"AMDisbetter!", CPU_Vendor::AMD},        {"AuthenticAMD", CPU_Vendor::AMD},
     {"GenuineIntel", CPU_Vendor::INTEL},      {"VIA VIA VIA ", CPU_Vendor::VIA},
     {"TransmetaCPU", CPU_Vendor::TRANSMETA},  {"GenuineTMx86", CPU_Vendor::TRANSMETA},
     {"CyrixInstead", CPU_Vendor::CYRIX},      {"CentaurHauls", CPU_Vendor::CENTAUR},
     {"NexGenDriven", CPU_Vendor::NEXGEN},     {"UMC UMC UMC ", CPU_Vendor::UMC},
     {"SiS SiS SiS ", CPU_Vendor::SIS},        {"Geode by NSC", CPU_Vendor::NSC},
     {"RiseRiseRise", CPU_Vendor::RISE},       {"Vortex86 SoC", CPU_Vendor::VORTEX},
     {"GenuineAO486", CPU_Vendor::AO486},      {"MiSTer AO486", CPU_Vendor::AO486},
     {"  Shanghai  ", CPU_Vendor::ZHAOXIN},    {"HygonGenuine", CPU_Vendor::HYGON},
     {"E2K MACHINE ", CPU_Vendor::ELBRUS},     {"TCGTCGTCGTCG", CPU_Vendor::QEMU},
     {" KVMKVMKVM  ", CPU_Vendor::KVM},        {"VMwareVMware", CPU_Vendor::VMWARE},
     {"VBoxVBoxVBox", CPU_Vendor::VIRTUALBOX}, {"XenVMMXenVMM", CPU_Vendor::XEN},
     {"Microsoft Hv", CPU_Vendor::HYPERV},     {" prl hyperv ", CPU_Vendor::PARALLELS},
     {" lrpepyh vr ", CPU_Vendor::PARALLELS},  {"bhyve bhyve ", CPU_Vendor::BHYVE},
     {" QNXQVMBSQG ", CPU_Vendor::QNX}}};

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
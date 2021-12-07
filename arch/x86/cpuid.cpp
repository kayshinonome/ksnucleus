#include <arch/x86/cpuid.hpp>

void cpuid::cpuid(uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx)
{
    // ecx is often an input as well as an output.
    asm volatile("cpuid" : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx) : "0"(*eax), "2"(*ecx));
}

uint32_t cpuid::highest_function_parameter()
{
    uint32_t eax = 0;
    uint32_t unused = 0;
    cpuid(&eax, &unused, &unused, &unused);
    return eax;
}

void cpuid::get_vendor_id(Array<char, 12> &buffer)
{
    uint32_t eax = 0;
    auto *raw_buffer = buffer.raw();

    // Load directly into the buffer from the cpuid helper function, which requires pointer arithmetic
    cpuid(&eax, reinterpret_cast<uint32_t *>(raw_buffer), reinterpret_cast<uint32_t *>(raw_buffer + 8),
          reinterpret_cast<uint32_t *>(raw_buffer + 4));
}

cpuid::CPU_Vendor cpuid::get_vendor()
{

    // NOTE: DO NOT, for any reason implement this with Table. You will inflate the binary by a lot as the compiler
    // decides to unroll the entire damn thing. I could work around this but also the effort of generating hashes for
    // these strings isnt work it because its only likely to be read a few time by the os

    static Atomic<bool> been_checked_before;
    static Atomic<CPU_Vendor> cached_cpu_vendor;

    if (been_checked_before)
    {
        return cached_cpu_vendor;
    }

    class CPU_String_Couple
    {
      public:
        String cpu_vendor_string;
        CPU_Vendor cpu_vendor;
    };

    const Array<CPU_String_Couple, 29> cpu_vendor_string_table{
        {{"GenuineIntel", CPU_Vendor::INTEL},      {"AMDisbetter!", CPU_Vendor::AMD},
         {"AuthenticAMD", CPU_Vendor::AMD},        {"VIA VIA VIA ", CPU_Vendor::VIA},
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

    Array<char, 12> buffer{};
    get_vendor_id(buffer);
    for (uint32_t x = 0, len = cpu_vendor_string_table.size(); x < len; x++)
    {
        // Get the vendor string as an array, cutting off that final byte
        const auto *array_tmp =
            reinterpret_cast<const Array<char, 12> *>(cpu_vendor_string_table[x].cpu_vendor_string.raw());
        if ((*array_tmp) == buffer)
        {
            been_checked_before = true;
            cached_cpu_vendor = cpu_vendor_string_table[x].cpu_vendor;
            return cached_cpu_vendor;
        }
    }

    been_checked_before = true;
    cached_cpu_vendor = CPU_Vendor::UNKNOWN;
    return cached_cpu_vendor;
}

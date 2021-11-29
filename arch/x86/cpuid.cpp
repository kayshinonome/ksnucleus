#include <arch/x86/cpuid.hpp>

void cpuid(size_t *eax, size_t *ebx, size_t *ecx, size_t *edx)
{
    // ecx is often an input as well as an output.
    asm volatile("cpuid" : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx) : "0"(*eax), "2"(*ecx));
}

uint32_t cpuid_highest_function_parameter()
{
    size_t eax = 0;
    size_t unused = 0;
    cpuid(&eax, &unused, &unused, &unused);
    return eax;
}

void cpuid_get_vendor_id(Array<char, 12> &buffer)
{
    size_t eax = 0;
    auto *raw_buffer = buffer.raw();

    // Load directly into the buffer from the cpuid helper function, which requires pointer arithmetic
    cpuid(&eax, reinterpret_cast<size_t *>(raw_buffer), reinterpret_cast<size_t *>(raw_buffer + 8),
          reinterpret_cast<size_t *>(raw_buffer + 4));
}

CPU_Vendor cpuid_get_vendor()
{
    CPU_Vendor vendor = CPU_Vendor::UNKNOWN;
    Array<char, 12> buffer{};
    constexpr Array<char, 12> empty_vendor{0};
    cpuid_get_vendor_id(buffer);
    if (buffer == empty_vendor)
    {
        ks_fission("Empty cpu vendor encountered. Likely bad cpuid code");
    }

    for (uint32_t x = 0, len = cpu_vendor_string_table.length(); x < len; x++)
    {
        // Get the vendor string as an array, cutting off that final byte
        auto *array_tmp = reinterpret_cast<Array<char, 12> *>(cpu_vendor_string_table[x].cpu_vendor_string.raw());
        if ((*array_tmp) == buffer)
        {
            vendor = cpu_vendor_string_table[x].cpu_vendor;
        }
    }
    return vendor;
}
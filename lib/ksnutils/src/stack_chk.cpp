#include <core/ksnucleus.hpp>
#include <math.hpp>
#include <types.hpp>

extern "C"
{
    __attribute__((noreturn)) void __stack_chk_fail()
    {
        ks_fission("Stack smashing detected!");
        while (true)
        {
        }
    }

    __attribute__((noreturn)) void __stack_chk_fail_local()
    {
        __stack_chk_fail();
        while (true)
        {
        }
    }
}

// Long statement, but its needed in order to properly get a semi random number
__attribute__((used)) uintptr_t __stack_chk_guard =
    (__TIME__[__SIZEOF_POINTER__] ^ __DATE__[__SIZEOF_FLOAT__] ^ __FILE__[__SIZEOF_INT__]) % __UINTPTR_MAX__;

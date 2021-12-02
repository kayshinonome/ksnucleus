#include <atomic.hpp>
#include <core/ksnucleus.hpp>
#include <utils.hpp>

namespace __cxxabiv1
{

    using __guard = Atomic<int64_t>;

    extern "C"
    {
        int __cxa_guard_acquire(__guard *g)
        {
            return static_cast<int>(*reinterpret_cast<char *>(g) == 0);
        }

        void __cxa_guard_release(__guard *g)
        {
            *reinterpret_cast<char *>(g) = 1;
        }

	void __cxa_guard_abort(__guard *)
        {
            ks_fission("Static initialization aborted!");
        }
    }

} // namespace __cxxabiv1

extern "C"
{
    constexpr auto ATEXIT_MAX_FUNCS = 0xff;

    using uarch_t = unsigned int;

    struct atexit_func_entry_t
    {
        void (*destructor_func)(void *);
        void *obj_ptr;
        void *dso_handle;
    };

    atexit_func_entry_t __atexit_funcs[ATEXIT_MAX_FUNCS];
    uarch_t __atexit_func_count = 0;
    void *__dso_handle = nullptr;

    /**
     * @brief A pure virtual has been called (which is unusual), so the system has to die
     *
     */
    __attribute__((noreturn)) void __cxa_pure_virtual()
    {
        ks_fission("Pure virtual called!");
    }

    void __cxa_finalize(void *f)
    {
        uarch_t i = __atexit_func_count;
        if (f == nullptr)
        {
            while ((i--) != 0)
            {
                if (__atexit_funcs[i].destructor_func != nullptr)
                {
                    (*__atexit_funcs[i].destructor_func)(__atexit_funcs[i].obj_ptr);
                }
            }
            return;
        }

        while ((i--) != 0)
        {
            if (reinterpret_cast<void *>(__atexit_funcs[i].destructor_func) == f)
            {
                (*__atexit_funcs[i].destructor_func)(__atexit_funcs[i].obj_ptr);
                __atexit_funcs[i].destructor_func = nullptr;
            }
        }
    }
}

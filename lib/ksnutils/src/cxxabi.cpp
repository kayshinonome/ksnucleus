#include <utils.hpp>

namespace __cxxabiv1
{

    using __guard = int64_t __attribute__((mode(__DI__)));

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
        }
    }

} // namespace __cxxabiv1

extern "C"
{
    constexpr int ATEXIT_MAX_FUNCS = 0xff;

    using uarch_t = unsigned int;

    struct atexit_func_entry_t
    {
        void (*destructor_func)(void *);
        void *obj_ptr;
        void *dso_handle;
    };

    static atexit_func_entry_t __atexit_funcs[ATEXIT_MAX_FUNCS];
    static uarch_t __atexit_func_count = 0;
    static void *__dso_handle = nullptr;

    /**
     * @brief A pure virtual has been called (which is unusual), so the system has to die
     *
     */
    __attribute__((noreturn)) void __cxa_pure_virtual()
    {
        // Copeland::Api::Neutronium::fission("Pure virtual called");
        while (true)
        {
        }
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

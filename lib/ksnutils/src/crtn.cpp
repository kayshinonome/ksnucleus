using func_ptr = void (*)();

extern func_ptr _fini_array_start[];
extern func_ptr _fini_array_end[];

extern "C"
{
    void _fini(void)
    {
        for (auto *func = reinterpret_cast<func_ptr *>(_fini_array_start);
             func != reinterpret_cast<func_ptr *>(_fini_array_end); func++)
        {
            (*func)();
        }
    }
}
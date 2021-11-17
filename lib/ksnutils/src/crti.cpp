using func_ptr = void (*)();

extern func_ptr _init_array_start[];
extern func_ptr _init_array_end[];

extern "C"
{
    void _init(void)
    {
        for (auto *func = reinterpret_cast<func_ptr *>(_init_array_start);
             func != reinterpret_cast<func_ptr *>(_init_array_end); func++)
        {
            if (func != nullptr)
            {
                (*func)();
            }
        }
    }
}

using func_ptr = void (*)();

extern func_ptr _init_array_start[];
extern func_ptr _init_array_end[];

extern "C"
{
    void _init(void)
    {
        for (func_ptr *func = _init_array_start; func != _init_array_end; func++)
        {
            (*func)();
        }
    }
}

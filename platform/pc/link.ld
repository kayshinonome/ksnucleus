ENTRY(_start)

SECTIONS
{
    . = 1M;

    .text ALIGN(4K) : 
    {
        . = ALIGN(8);
        KEEP(*(.multiboot))
        . = ALIGN(4K);
        *(.text*)
    }

    .init_array :
    {
        _init_array_start = .;
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        _init_array_end = .;
    }

    .fini_array :
    {
        _fini_array_start = .;
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        _fini_array_end = .;
    }
   
    .rodata ALIGN(4K) :
    {
        *(.rodata*)
    }

    .data ALIGN(4K) : 
    {
        *(.data*)
    }

    .bss ALIGN(4K) : 
    {
        *(.bss*) 
        *(COMMON)
    }
}

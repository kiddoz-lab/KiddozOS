ENTRY(_start)

SECTIONS
{
    . = 0x8000;

    .text : ALIGN(4)
    {
        *(.text*)
    }

    .rodata : ALIGN(4)
    {
        *(.rodata*)
    }

    .data : ALIGN(4)
    {
        *(.data*)
    }

    .bss : ALIGN(4)
    {
        *(.bss*)
        *(COMMON)
    }

    /DISCARD/ :
    {
        *(.ARM.exidx*)
        *(.ARM.extab*)
        *(.eh_frame*)
        *(.note.gnu.build-id*)
    }
}
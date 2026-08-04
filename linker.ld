ENTRY(_start)

MEMORY
{
    ram (rwx) : ORIGIN = 0x00100000, LENGTH = 16M
}

SECTIONS
{
    . = ORIGIN(ram);

    .text : AT(ORIGIN(ram)){
        *(.text)
    } > ram
    .rodata : {
        *(.rodata*)
    } > ram
    .data : {
        *(.data*)
    } > ram
    .bss : {
        *(.bss*)
        *(.COMMON)
    } > ram
}
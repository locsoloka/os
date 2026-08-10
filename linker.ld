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
        . = ALIGN(4); /* 4 bájtos igazítás a biztonság kedvéért */
        _end = .;    /* <-- EZ A KULCS! Itt ér véget az összes statikus adat! */
    } > ram
}
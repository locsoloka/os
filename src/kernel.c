#include "IO/keyboard.h"

#include "grapics/screen.h"

void kernel_main(void) {
    int cursor = 0;

    volatile char* vga = (volatile char*) 0xB8000;


    clear_screen();
    
    char* msg = "Tirpak OS";
    
    cursor = kprint(msg, cursor);
    cursor = kline_break(cursor);
    unsigned char usr_I = get_char();

    vga[cursor * 2] = usr_I;
    vga[cursor * 2 + 1] = 0x0F;
}
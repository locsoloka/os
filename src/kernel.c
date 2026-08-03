#include "IO/keyboard.h"

#include "grapics/screen.h"

void kernel_main(void) {
    // A VGA memória címe, ide írva jelenik meg a szöveg a képernyőn
    volatile char* vga = (volatile char*) 0xB8000;
    int cursor = 0;

    clear_screen();
    
    char* msg = "Tirpak OS";
    
    cursor = kprint(msg, cursor);

    // for (int i = 0; msg[i] != '\0'; i++) {
    //     vga[i * 2] = msg[i];      // Karakter
    //     vga[i * 2 + 1] = 0x0F;    // Szín (fekete alapon fehér)
    //     cursor++;
    // }
    unsigned char usr_I = get_char();

    vga[cursor * 2] = usr_I;
    vga[cursor * 2 + 1] = 0x2F;

}
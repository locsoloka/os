#include "IO/keyboard.h"

#include "memory_managment/memory_allocator.h"

#include "grapics/screen.h"

#include "shell/shell_main.h"

void kernel_main(void) {
    int cursor = 0;

    volatile char* vga = (volatile char*) 0xB8000;


    clear_screen();
    
    char* msg = "Tirpak OS";
    
    cursor = kprint(msg, cursor);
    cursor = kline_break(cursor);

    char *buffer = kstack_alloc(128);

    kfscan(buffer, cursor);
    cursor = kline_break(cursor);
    cursor = kprint(buffer, cursor);

    char *test[] = {"clear"};

    execute_command(1, test, cursor);
}
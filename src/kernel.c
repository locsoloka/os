#include "IO/keyboard.h"

#include "memory_managment/memory_allocator.h"

#include "grapics/screen.h"

#include "shell/shell_main.h"

void kernel_main(void) {
    grapics_init();
    clear_screen();
    
    char* msg = "Tirpak OS";

    kprint(msg);
    kline_break();

    char *buffer = kstack_alloc(128);

    kfscan(buffer);
    kline_break();
    kprint("fasz");

    char *test[] = {"clear"};

    execute_command(1, test);
}
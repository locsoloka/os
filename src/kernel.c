#include <stdbool.h>

#include "IO/keyboard.h"
#include "memory_managment/memory_allocator.h"
#include "grapics/screen.h"
#include "shell/shell_main.h"
#include "shell/shell_helpers.h"
#include "IO/file_managment/ata_drivers.h"

int argc = 0;

void kernel_main(void) {
    grapics_init();
    clear_screen();
    
    char* msg = "Tirpak OS";

    kprint(msg);
    kline_break();

    uint8_t *buffer = kstack_alloc(256);

    ata_read_sector(1, buffer);

    // ata_write_sector(1, "Ciagnyokat verem");

    for  (int i = 0; i < 256; i++)
    {
        kprint_ch(buffer[i]);
    }
    
    
    kline_break();
    kprint("Read end");
    //while (true)
    //{
    //    kfscan(buffer);
    //    kline_break();
//
    //    tokenize(buffer, &argc);
    //    execute_command(1, &buffer);
    //}
}
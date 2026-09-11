#include <stdbool.h>

#include "IO/keyboard.h"
#include "memory_managment/memory_allocator.h"
#include "grapics/screen.h"
#include "shell/shell_main.h"
#include "shell/shell_helpers.h"
#include "IO/file_managment/ata_drivers.h"
#include "IO/file_managment/fat.h"

int argc = 0;

void kernel_main(void) {
    grapics_init();
    clear_screen();
    
    char* msg = "Tirpak OS";

    kprint(msg);
    kline_break();

    uint8_t *sector_buffer = kstack_alloc(512);

    ata_read_sector(0, sector_buffer);

    fat16_boot_sector_t *bs = (fat16_boot_sector_t *)sector_buffer;

    uint32_t fat_lba = bs->reserved_sectors;
    uint32_t root_dir_lba = fat_lba + (bs->fat_count * bs->sectors_per_fat);
    uint32_t root_dir_sectors = (bs->root_entry_count * 32) / bs->bytes_per_sector;
    uint32_t data_lba = root_dir_lba + root_dir_sectors;

    for  (int i = 0; i < 512; i++)
    {
        kprint_ch(sector_buffer[i]);
    }
    
    kline_break();
    kprint("Read end");
    kline_break();
    file_init();
    kprint("file_init");
    find_LBA();
    file_lookup();
}

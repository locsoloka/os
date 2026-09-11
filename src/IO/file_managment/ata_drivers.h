#include <stdint.h>

#ifndef ATA_DRIVERS_H_DEFINED
#define ATA_DRIVERS_H_DEFINED

void ata_read_sector(uint32_t lba, uint8_t *buffer);
void ata_write_sector(uint32_t lba, uint8_t *buffer);

#endif
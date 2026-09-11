#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../grapics/screen.h"

const uintptr_t Status_address = 0x01F7;

volatile uint16_t *Status = (volatile uint16_t*) Status_address;

uint8_t byte_value = 0;

static inline uint8_t inb(uint16_t port) // read 8 bit
{
    uint8_t result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

static inline void outb(uint16_t port, uint8_t val) // write 8 bit
{
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint16_t inw(uint16_t port) // read 16 bit
{
    uint16_t result;
    __asm__ volatile ("inw %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

static inline void outw(uint16_t port, uint16_t val) // write 16 bit
{
    __asm__ volatile ("outw %0, %1" : : "a"(val), "Nd"(port));
}

void wait_400ns()
{
    for (int i = 0; i < 4; i++)
    {
        inb(0x1F7);
    }
}

void ata_read_sector(uint32_t lba, uint8_t *buffer)
{
    while ((inb(0x1F7) & 0x80)) {} // Wait till drive not BSY

    outb(0x1F6, 0xE0); // drive selection for LBA mode plus master

    outb(0x1F2, 1); // How many sectors do we want to read

    outb(0x1F3, (uint8_t)lba);
    outb(0x1F4, (uint8_t)(lba >> 8));
    outb(0x1F5, (uint8_t)(lba >> 16));
    outb(0x1F6, 0xE0 | ((lba >> 24) & 0x0F)); // Master drive + LBA

    outb(0x1F7, 0x20); // Read sectors command

    wait_400ns();
    while ((inb(0x1F7) & 0x08) == 0) {} // Polling for DRQ bit

    uint16_t *buf16 = (uint16_t *)buffer;
    for (int i = 0; i < 256; i++)
    {
        buf16[i] = inw(0x1F0);
    }
}

void ata_write_sector(uint32_t lba, uint8_t *buffer)
{
    while ((inb(0x1F7) & 0x80)) {} // Wait till drive not BSY

    outb(0x1F6, 0xE0); // drive selection for LBA mode plus master

    outb(0x1F2, 1); // How many sectors do we want to write

    outb(0x1F3, (uint8_t)lba);
    outb(0x1F4, (uint8_t)(lba >> 8));
    outb(0x1F5, (uint8_t)(lba >> 16));
    outb(0x1F6, 0xE0 | ((lba >> 24) & 0x0F)); // Master drive + LBA

    outb(0x1F7, 0x30); // Read sectors command
    
    wait_400ns();
    while ((inb(0x1F7) & 0x80)) {} // Wait till drive not BSY

    uint16_t *buf16 = (uint16_t *)buffer;
    for (int i = 0; i < 256; i++)
    {
        outw(0x1F0, buf16[i]);
    }

}

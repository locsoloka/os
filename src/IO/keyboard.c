#include "../grapics/screen.h"
#include <stdbool.h>


const char scancode_to_ascii_map[] = {
    0,   27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
     0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
     0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
   '*',   0, ' '
};

static inline unsigned char inb(unsigned short port)
{
    unsigned char result;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

unsigned char read_keyboard_scancode(void)
{
    while ((inb(0x64) & 1) == 0) {}
    return inb(0x60);
}

unsigned char scancode_to_ascii(void)
{
    unsigned char scancode = read_keyboard_scancode();
    if (scancode < sizeof(scancode_to_ascii_map))
    {
        return scancode_to_ascii_map[scancode];
    }
    return '\0';
}

char get_char(void)
{
    unsigned char ch = scancode_to_ascii();
    return ch;
}

volatile char* vga = (volatile char*) 0xB8000;


void kfscan(char *buf)
{
    buf[0] = 'A';
    int i = 0;
    while (true)
    {
        
        char ch = get_char();
        buf[i] = ch;
        if (buf[i] == '\n')
        {
            buf[i] = '\0';
            i++;
            return;
        }
        else if (buf[i] == '\0')
        {

        }
        else
        {
            kprint_ch(ch);
            i++;
        }
    }
}


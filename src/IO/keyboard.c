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
//    if (scancode < sizeof(scancode_to_ascii_map))
//    {
        return scancode_to_ascii_map[scancode];
//    }
}

unsigned char get_char(void)
{
    unsigned char ch = scancode_to_ascii();
    return ch;
}
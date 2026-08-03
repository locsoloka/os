void clear_screen(void)
{
    volatile char* vga = (volatile char*) 0xB8000;

    for (int i = 0; i < 80 * 25; i++)
    {
        vga[i * 2] = ' ';
        vga[i * 2 + 1] = 0x00;
    }
}

int kprint(char *text, int cursor)
{
    volatile char* vga = (volatile char*) 0xB8000;

    for (int i = 0; text[i] != '\0'; i++)
    {
        vga[cursor * 2] = text[i];
        vga[cursor * 2 + 1] = 0x0F;
        cursor++;
    }
    return cursor;
}
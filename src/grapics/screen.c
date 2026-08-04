#define ROW 25
#define COL 80

void clear_screen(void)
{
    volatile char* vga = (volatile char*) 0xB8000;

    for (int i = 0; i < COL * ROW; i++)
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

int kline_break(int cursor)
{
    if (cursor >= (COL * (ROW - 1)) + 1)
    {
        clear_screen();
        cursor = 0;
    }
    else
    {
        cursor += COL - (cursor % COL);
    }
    return cursor;
}
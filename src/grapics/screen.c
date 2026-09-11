#define ROW 25
#define COL 80

static int cursor;

void kline_break(void); 

void grapics_init(void)
{
    cursor = 0;
}

void clear_screen(void)
{
    volatile char* vga = (volatile char*) 0xB8000;

    for (int i = 0; i < COL * ROW; i++)
    {
        vga[i * 2] = ' ';
        vga[i * 2 + 1] = 0x00;
    }
}

void kprint(char *text)
{
    volatile char* vga = (volatile char*) 0xB8000;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '\n')
        {
            kline_break();
        }
        else
        {
            vga[cursor * 2] = text[i];
            vga[cursor * 2 + 1] = 0x0F;
            cursor++;
        }
    }
}

void kprint_raw(char *text)
{
    volatile char* vga = (volatile char*) 0xB8000;

    for (int i = 0; text[i] != '\0'; i++)
    {
        vga[cursor * 2] = text[i];
        vga[cursor * 2 + 1] = 0x0F;
        cursor++;
    }
}



void kprint_ch(char text)
{
    volatile char* vga = (volatile char*) 0xB8000;
    if (text == '\n')
    {
        kline_break();
    }
    else if (text > 32 && text < 128)
    {
        vga[cursor * 2] = text;
        vga[cursor * 2 + 1] = 0x0F;
        cursor++;
    }
}

void kprint_ch_raw(char text)
{
    volatile char* vga = (volatile char*) 0xB8000;
    vga[cursor * 2] = text;
    vga[cursor * 2 + 1] = 0x0F;
    cursor++;
}

void kline_break(void)
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
}

char int_to_char(int number)
{
    // if (number >= 48 && number <= 57)
    // {
    //     char ch = number + 48;
    //     return ch;
    // }    
    return number + 48;
}

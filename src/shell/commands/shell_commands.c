#include "../../grapics/screen.h"
#include "../../IO/file_managment/fat.h"

int clear(int argc, char *argv[])
{
    clear_screen();
    return 0;
}

int list_current_dir(int argc, char *argv[])
{
    file_lookup_current();
    return 0;
}

int change_directory_command(int argc, char *argv[])
{
    kline_break();
    kprint(argv[1]);
    change_directory(argv[1]);
    return 0;
}
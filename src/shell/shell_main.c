#include <stddef.h>

#include "../lib/std_lib/string/string.h"

#include "../grapics/screen.h"

#include "commands/shell_commands.h"

typedef int (*cmd_func_t)(int argc, char *argv[]);

typedef struct {
    const char *name;      // A parancs neve (pl. "clear")
    cmd_func_t func;       // A függvény, amit meg kell hívni
    const char *help;      // Súgó szöveg
} command_t;

static const command_t cmd_table[] = 
{
  // {"help",  help,  "Megjeleniti a megadott parancsokat"},
  {"clear", clear, "Clear the screeen"},
  // {"echo",  echo,  "Kiirja a megadott argumentumokat"},
  {NULL,    NULL,      NULL}
};

void execute_command(int argc, char *argv[])
{
  if (argc == 0 || argv == NULL)
  {
    kprint("NULL");
    return;
  }
  for (int i = 0; cmd_table[i].func != NULL; i++)
  {
    if (strcmp(cmd_table[i].name, argv[0]) == 0)
    {
      kprint(cmd_table[i].name);
      cmd_table[i].func(argc, argv);
      return;
    }
  }
  kprint("Command not found");
  return;
}

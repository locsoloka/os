#include <stddef.h>

#include "../lib/std_lib/string/string.h"

#include "../grapics/screen.h"

#include "commands/shell_commands.h"

typedef int (*cmd_func_t)(int argc, char *argv[]); // Standard function ptr 

typedef struct {
    const char *name;      // A command name for example "clear"
    cmd_func_t func;       // The function to be called
    const char *help;      // Help test
} command_t;

/*{"user input", function ptr, help text}*/
static const command_t cmd_table[] = 
{
  {"clear", clear, "Clear the screeen"}, 
  
  {"cd", change_directory_command, "Change directory"},
  {"ls", list_current_dir, "List every file and directory in current folder"},
  
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
  kline_break();
  return;
}

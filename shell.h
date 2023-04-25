#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>
#include <stdbool.h>

/* Constants */
#define SHELL_INPUT_SIZE 1024
#define SHELL_TOKEN_DELIMITERS " \t\r\n\a"

/* Function prototypes */
void shell_loop(void);
char *shell_read_line(void);
char **shell_split_line(char *line);
int shell_execute(char **args);
int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);

#endif

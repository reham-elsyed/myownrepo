#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <dirent.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
/*---Macros---*/
#define TOK_DELIM " \t\r\n\a\""
#define MAX_INPUT_LENGTH 1024
#define BUF_FLUSH -1
extern char **environ;
/*---PROTOTYPES---*/
/* main_shell function */
int main(void);
/**get env to set path*/
char *_getenv(const char *name);
/**tokenize command input**/
char **line_token(char *line);

/** printprompt-readcommand--*/
char *read_command(void);

/**stringto token**/
char *_strtok(char *str, const char *delim);
/**printing functions**/
void _puts(char *str);
int _putchar(char c);
int _strlen(char *c);
/**string compare function**/
int _strcmp(char *haystack, char *needle);
/**compare string to character**/
char *_strchr(const char *str, int c);
/** execve function**/
int execve(const char *pathname, char *const argv[], char *const envp[]);
int execute(char **argv);

char *search_path(char *file);
int execute_cd(char **args);
int execute_chdir(char **args);
int execute_mkdir(char **args);
int _create_file(char **args);
int execute_echo(char **args);
int listCurrentDirectory(char **args);
typedef struct {
  char *name;
  int (*func)(char **);
} Command;
#endif

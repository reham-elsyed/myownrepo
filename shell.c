#include "shell.h"
/**struct */
Command commands[] = {{"cd", execute_cd},
{"ls", listCurrentDirectory},
{"chdir", execute_chdir},
{"mkdir", execute_mkdir},
{"touch", _create_file},
{NULL, NULL}};

/**
 * _strlen - function returns length of string
 * @c: string input
 * Return: intger
 */
int _strlen(char *c) {
int i = 0;
if (!c)
return (0);
while (*c++)
i++;
return (i);
}
/**
 * create_file - function to create file
 * @filename: input file name
 * @text_content: input text content
 * Return: 1 in success, -1 failure
 */
int _create_file(char **args)
{
int fd;
ssize_t bytes = 0;

if (!args[1]) {
return -1;
}
fd = open(args[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
if (fd == -1) {
perror("open");
return -1;
}
if (bytes == -1) {
perror("write");
close(fd);
return -1;
}
if (close(fd) == -1)
{
perror("close");
return (-1);
}
return (1);
}
/**
 *execute_mkdir - function to create directory
 *@args: input arguments
 *Return: 1 in success, -1 failure
 */
int execute_mkdir(char **args) {

  if (args[1] == NULL) {
    fprintf(stderr, "mkdir: missing opperand/n");
  }
  if (mkdir(args[1], 0777) != 0) {
    perror("mkdir");
  }
  return (1);
}
/**
 *execute_cd - function to create directory
 *@args: input arguments
 *Return: 1 in success, -1 failure
 */
int execute_cd(char **args) {
  char cwd[MAX_INPUT_LENGTH];
  if (args[1] == NULL) {
    fprintf(stderr, "Expected argument to \"cd\"\n");
  } else if (chdir(args[1]) != 0) {
    perror("shell");
    printf("error in execute cd");
  } else {
    if (getcwd(cwd, sizeof(cwd)) != NULL) {

      _puts(cwd);
    }
    return (0);
  }
  return (1);
}
/**
 *execute_chdir - function to create directory
 *@args: input arguments
 *Return: 1 in success, -1 failure
 */
int execute_chdir(char **args)
{
if (chdir(args[1]) == -1)
{
switch (errno) {
case ENOENT:
_puts("Unable to locate the directory");
_puts(args[1]);
_puts("\n");
break;
case EINVAL:
_puts("Invalid buffer.\n");
break;
default:
_puts("Unknown error.\n");
}
}
else
{
if (system("ls") != 0)
{
  perror("ls");}
}
return (1);
}
/**
 *search_path- function to create directory
 *@file: input arguments
 *Return: 1 in success, -1 failure
 */
char *search_path(char *file) {
  char *path= _getenv("PATH");
  char *p;
  char *fullpath;

if (file == NULL)
	return (NULL);
if (path == NULL)
return (NULL);
p = _strtok(path, ":");
fullpath = malloc(4097);
while (p != NULL)
{
sprintf(fullpath, "%s/%s", p, file);
if (access(fullpath, F_OK) == 0)
{
return (fullpath);
}
p = _strtok(NULL, ":");
}
free(fullpath);
return (NULL);
}
/**
 *execute - function to create directory
 *@argv: input arguments
 *Return: 1 in success, -1 failure
 */
int execute(char **argv)
{
pid_t pid;
int status, i;
char *fullpath;
int result;
setenv("PATH", "/testingshell", 1);
for (i = 0; commands[i].name != NULL; i++)
{
if (strcmp(argv[0], commands[i].name) == 0)
{
result = commands[i].func(argv);
if (result == -1)
fprintf(stderr, "Error executing %s\n", argv[0]);
return (result);
}
}
pid = fork();

if (pid == -1)
{
perror("Fork failed");
return (-1);
}
else if (pid == 0)
{
/*Child process*/
fullpath = search_path(argv[0]);
if (fullpath == NULL)
{
char *message = ": command not found\n";
_puts(argv[0]);
_puts(message);
_exit(EXIT_FAILURE);
}
if (execve(fullpath, argv, NULL) == -1)
{
perror("Execve failed");
free(fullpath);
_exit(EXIT_FAILURE);
}
free(fullpath);
}
else
{
/* Parent process*/
do
{
waitpid(pid, &status, WUNTRACED);
} 
while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
return (0);
}

/**
 *_putchar - function print
 *@args: input arguments
 *Return: 1 in success, -1 failure
 */

int _putchar(char c)
{
return (write(1, &c, 1));
}


/**
 *read_command - function to get command input from user
 *Return:line input by user
 */
char *read_command(void)
{
char *command = NULL;
size_t buf = 0;
char c[] = {"$"};
_puts(c);
if (getline(&command, &buf, stdin) == -1)
{
if (feof(stdin))
{
free(command);
exit(EXIT_SUCCESS);
printf("this is feof in read cmand\n");
}
else
{
free(command);
perror("error while reading the line from stdin");
exit(EXIT_FAILURE);
printf("error reading fromstdn\n");
}
}
return (command);
}

/**
 * _puts - function that print string
 * @str: input value
 * Return nothing
 */
void _puts(char *str)
{
int i = 0;
if (!str)
return;
while (str[i] != '\0')
{
_putchar(str[i]);
i++;
}
}

/**
 * main_shell - main function fotshell program
 * Read line with prompt
 * Tokenize the line.
 * Return: 0 if success
 */
int main(void)
{
int i;
char *line;
char **args;
int status = -1;
while (status == -1)
{
line = read_command();
args = line_token(line);

if (args[0] != NULL)
{
status = execute(args);
if (status < 0)
{
fprintf(stderr, "Error executing the command\n");
}
}
free(line);
for (i = 0; args[i] != NULL; i++)
{
free(args[i]);
}
free(args);
if (status >= 0)
{
status = -1;
}
}
return (0);
}


/**
 * line_token - function to get token from input line(command)
 * @line: input line
 * Return: args
 */
char **line_token(char *line) {
  char *token;
  int i = 0;
  char **args = malloc(sizeof(char *) * (MAX_INPUT_LENGTH + 1));
printf("didwe malloc in linetoken?\n");
if (!args)
{
perror("Memory allocation error");
exit(EXIT_FAILURE);
printf("noargs in line tok\n");
}
token = _strtok(line, TOK_DELIM);
while (token != NULL)
{
if (i >= MAX_INPUT_LENGTH)
{
fprintf(stderr, "Too many arguments\n");
exit(EXIT_FAILURE);
}
args[i] = strdup(token);
if (!args[i])
{
perror("Memory allocation error");
exit(EXIT_FAILURE);
}
i++;
token = _strtok(NULL, TOK_DELIM);
}
args[i] = NULL;
return (args);
}

char *_strtok(char *s, const char *delim)
{
static char *p = NULL;
(void)delim;

if (s == NULL)
{
s = p;
if (s == NULL)
{
return (NULL);
}
}

s += strspn(s, TOK_DELIM);
if (*s == '\0')
{
p = NULL;
return (p);
}
p = s + strcspn(s, TOK_DELIM);
if (*p != '\0')
{
*p = '\0';
p++;
}
else
{
p = NULL;
}
printf("this it tokenization success\n");
return (s);
}

char *_getenv(const char *name)
{
extern char **environ;
char **env = environ;

while (*env)
{
if (strncmp(*env, name, strlen(name)) == 0 && (*env)[strlen(name)] == '=') {
return (&(*env)[strlen(name) + 1]);
}
env++;
}
return (NULL);
}

int listCurrentDirectory(char **args)
{
  DIR *dp;
struct dirent *entry;
(void)args;

  dp = opendir(".");

if (dp == NULL)
{
perror("opendir");
exit(EXIT_FAILURE);
}
while ((entry = readdir(dp))) {
if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
printf("%s\n", entry->d_name);
}
}
closedir(dp);
return (1);
}

#include "shell.h"

/**
 * main - Entry point of the shell program
 * Return: Always 0
 */

int main(void)
{
	shell_loop();
	return (0);
}

/**
 * shell_loop - Function that loops through the shell
 */

void shell_loop(void)
{
	char *line, **args;
	int status;

	do {
	printf("shell$ ");
	line = shell_read_line();
	args = shell_split_line(line);
	status = shell_execute(args);
	free(line), free(args);
	}
}

/**
 * shell_read_line - Function that reads the input from the user
 * Return: The line of input
 */

char *shell_read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	exit(errno);
	return (line);
}

/**
 * shell_split_line - Function that splits the line of input into arguments
 * @line: The line of input to split
 * Return: The arguments as an array of strings
 */

char **shell_split_line(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	exit(errno);
	token = strtok(line, SHELL_TOKEN_DELIMITERS);
	while (token != NULL)
	{
	tokens[position++] = token;
	if (position >= bufsize)
	{
	bufsize += 64;
	tokens = realloc(tokens, bufsize * sizeof(char *));
	if (!tokens)
	exit(errno);
	}
	token = strtok(NULL, SHELL_TOKEN_DELIMITERS);
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * shell_execute - Function that executes a command
 * @args: The arguments for the command
 * Return: 1 if successful, 0 if not
 */

int shell_execute(char **args)
{
	if (!args[0])
	return (1);
	if (strcmp(args[0], "cd") == 0)
	return (shell_cd(args));
	if (strcmp(args[0], "help") == 0)
	return (shell_help(args));
	if (strcmp(args[0], "exit") == 0)
	return (shell_exit(args));
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
	if (execvp(args[0], args) == -1)
	exit(errno);
	}
	else if (pid < 0)
	{
	exit(errno);
	}
	else
	{
	do
	wpid = waitpid(pid, &status, WUNTRACED);
	while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}

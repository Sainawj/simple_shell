#include "shell.h"

/**
 * main - Simple shell program
 *
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
	char *line, **argv;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		printf("$ ");
		read = getline(&line, &len, stdin);

		if (read == -1)
			return (printf("\n") == EOF ? 1 : 0);

		argv = split_line(line);
		if (!argv)
			perror("Error"), exit(1);

		if (!fork())
			return (execve(argv[0], argv, NULL) == -1 ?
				perror("Error"), free_argv(argv), 1 :
				free_argv(argv), 0);
		else if (wait(NULL) == -1)
			perror("Error"), free_argv(argv), exit(1);

		free_argv(argv);
	}

	free(line);
	return (0);
}


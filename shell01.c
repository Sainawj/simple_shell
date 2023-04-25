#include "shell.h"

/**
 * main - Entry point for the shell program
 *
 * Return: 0 on success, otherwise a non-zero value on failure
 */
int main(void)
{
	char *line = NULL, *argv[2];
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		printf("$ ");
		read = getline(&line, &len, stdin);

		if (read == -1)
			return (printf("\n") == EOF ? EXIT_FAILURE : EXIT_SUCCESS);

		argv[0] = line, argv[1] = NULL;

		if (!fork())
			return (execve(argv[0], argv, NULL) == -1 ?
				perror("Error"), EXIT_FAILURE : EXIT_SUCCESS);
		else if (wait(NULL) == -1)
			perror("Error"), exit(EXIT_FAILURE);
	}

	return (0);
}


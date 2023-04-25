#include "shell.h"

/**
 * main - Entry point for the shell program
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	char *argv[3];
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		printf("$ ");
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		argv[0] = strtok(line, " \n");
		argv[1] = strtok(NULL, " \n");
		argv[2] = NULL;

		if (strcmp(argv[0], "exit") == 0)
			exit(EXIT_SUCCESS);

		pid_t pid = fork();

		if (pid == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			execve(argv[0], argv, NULL);
			perror("Error");
			exit(EXIT_FAILURE);
		}
		else
			wait(NULL);
	}

	return (0);
}


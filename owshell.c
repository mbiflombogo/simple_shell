#include "sshell.h"
/**
  * main - program entrance
  * @argc: arg count
  * @argv: name of program
  * Return: int
  */
int main(__attribute__((unused))int argc, __attribute__((unused))char **argv)
{
	loop();
	return (EXIT_SUCCESS);
}
/**
  * loop - keep displaying prompt
  */
void loop(void)
{
	char *line;
	char **args;
	int status;

	do {
		printf("($) ");
		line = read_line();
		args = split_line(line);
		status = execute(args);
		free(line);
		free(args);
	} while (status);
}
/**
  * read_line - read user input
  * Return: array of chars
  */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
			exit(EXIT_SUCCESS);
		else
		{
			perror("readline");
			exit(EXIT_FAILURE);
		}
	}
	return (line);
}
#define SL_BUFSIZE 64
#define SL_DELIM " \t\r\n\a"
/**
  * split_line - split input into cmds
  * @line: user input
  * Return: array of ptrs to strs
  */
char **split_line(char *line)
{
	int postn = 0;
	int bufsize = SL_BUFSIZE;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "owsh: allocation err\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, SL_DELIM);
	while (token != NULL)
	{
		tokens[postn] = token;
		postn++;
		if (postn >= bufsize)
		{
			bufsize += SL_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "owsh: allocation err\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, SL_DELIM);
	}
	tokens[postn] = NULL;
	return (tokens);
}
/**
  * launch - fork a child
  * @args: array of ptrs to strs
  * Return:  pid of changed state
  */
int launch(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
			perror("owsh");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("owsh");
	else
	{
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (wpid);
}

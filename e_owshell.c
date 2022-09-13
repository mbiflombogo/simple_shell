#include "sshell.h"
/**
  * execute - execute commands
  * @args: cmdline to execute
  * Return: type int
  */
int execute(char **args)
{
	int i;
	char *b_str[] = {
		"cd",
		"exit"
	};
	int (*b_func[])(char **) = {
		&c_d,
		&ex_it
	};

	if (args[0] == NULL)
		return (1);
	for (i = 0; i < builtins(); i++)
	{
		if (_strcmp(args[0], b_str[i]) == 0)
			return ((*b_func[i])(args));
	}
	return (launch(args));
}
/**
  * builtins - check for builtins
  * Return: type int
  */
int builtins(void)
{
	char *b_str[] = {
		"cd",
		"exit"
	};

	return (sizeof(b_str) / sizeof(char *));
}
/**
  * c_d - change dir
  * @args: arguments
  * Return: 1
  */
int c_d(char **args)
{
	if (args[1] == NULL)
		fprintf(stderr, "owsh: missing arg to \"cd\"\n");
	else
	{
		if (chdir(args[1]) != 0)
			perror("owsh");
	}
	return (1);
}
/**
  * ex_it - quit shell
  * @args: arguments
  * Return: 0
  */
int ex_it(__attribute__((unused))char **args)
{
	return (0);
}

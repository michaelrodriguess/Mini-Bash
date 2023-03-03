//HEADER

#include "../../includes/minishell.h"

void ft_echo(char **args)
{
	int	n;

	n = 1;
	if (!ft_strcmp(*args, "-n"))
	{
		n = 0;
		args++;
	}
	while (*args)
	{
		printf("%s", *args);
		if (args[1] != NULL)
			printf(" ");
		args++;
	}
	if (n)
		printf("\n");
}

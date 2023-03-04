//HEADER

#include "../../includes/minishell.h"

void ft_cd(char **path)
{
	int	sz;

	sz = 0;
	while (path[sz])
		sz++;
	if (sz > 2)
			printf("too many arguments\n");
	if (chdir(path[0]))
		ft_printf ("No such file or directory\n");
}

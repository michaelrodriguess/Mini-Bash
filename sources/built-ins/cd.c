//HEADER

#include "../../includes/minishell.h"

void ft_cd(char **path)
{
	int	sz;

	sz = 0;
	if (path == NULL)
		return;
		//get HOME from env
	while (path[sz])
		sz++;
	if (sz > 1)
			printf("too many arguments\n");
	else if (chdir(path[0]))
		ft_printf ("No such file or directory\n");
}

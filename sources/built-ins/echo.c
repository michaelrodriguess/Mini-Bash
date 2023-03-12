/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:52:54 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/06 11:53:04 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char **args)
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

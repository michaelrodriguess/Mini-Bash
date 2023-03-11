/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:41:16 by microdri          #+#    #+#             */
/*   Updated: 2023/03/11 18:42:39 by microdri         ###   ########.fr       */
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

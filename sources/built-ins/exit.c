/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:15:28 by microdri          #+#    #+#             */
/*   Updated: 2023/03/29 14:33:40 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	verify_only_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
				i++;
		else
			return (1);
	}
	return (0);
}

void	ft_exit(char **args)
{
	if (args == NULL)
		exit(EXIT_SUCCESS);
	else if (args[1] != NULL)
	{
		message_error("microtano: exit: too many arguments\n", 1);
	}
	else if (verify_only_num(*args) == 1)
	{
		message_error("microtano: exit: numeric argument required\n", 255);
		exit(var_global);
	}
	else if (ft_isnum(ft_atoi(args[0]) == 1))
	{
		var_global = ft_atoi(args[0]);
		exit(var_global);
	}
}

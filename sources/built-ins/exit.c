/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:15:28 by microdri          #+#    #+#             */
/*   Updated: 2023/04/12 16:20:32 by microdri         ###   ########.fr       */
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
	if (args[1] != NULL)
	{
		write(2, "exit\n", 5);
		message_error("microtano: exit: too many arguments", 1);
		return ;
	}
	if (args == NULL)
		exit(EXIT_SUCCESS);
	else if (verify_only_num(*args) == 1)
	{
		message_error("microtano: exit: numeric argument required", 255);
		exit(g_var_global);
	}
	else if (ft_isnum(ft_atoi(args[0]) == 1))
	{
		g_var_global = ft_atoi(args[0]);
		exit(g_var_global);
	}
}

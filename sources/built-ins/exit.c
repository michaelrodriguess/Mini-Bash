/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:15:28 by microdri          #+#    #+#             */
/*   Updated: 2023/03/06 17:34:11 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int verify_only_num(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while(str[i]) 
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
	int temp_var_g;

	temp_var_g = 0;
	if (args == NULL)
		exit(EXIT_SUCCESS);
	else if (args[1] != NULL)
	{
		temp_var_g = 1;
		printf("bash: exit: too many arguments\n");
	}
	else if (verify_only_num(*args) == 1)
	{
		temp_var_g = 255;
		printf("microtano: exit: %s: numeric argument required\n", args[0]);
		exit(temp_var_g);
	}
//	else if (*args[0] >= 'a' && *args[0] <= 'z')
//	{
//		temp_var_g = 255;
//		printf("microtano: exit: %s: numeric argument required\n", args[0]);
//		exit(temp_var_g);
//	}	
	else if (ft_isnum(ft_atoi(args[0]) == 1))
	{
		temp_var_g = ft_atoi(args[0]);
		exit(temp_var_g);
	}
}

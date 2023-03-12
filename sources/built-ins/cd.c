/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:50:34 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/12 19:16:19 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_home(char **env)
{
	while (*env && ft_strncmp(*env, "HOME", ft_strchri(*env, '=') - 1))
		env++;
	if (!*env)
		return (NULL);
	return (&((*env)[5]));
}

void	ft_error(int err_n)
{
	ft_printf ("%i: No such directory\n", err_n);
}

void	ft_cd(char **args, char **env)
{
	char	*path;
	int		err_n;

	if (ft_array_len(args) <= 1)
	{
		if (args == NULL)
		{
			path = get_home(env);
			if (!path)
			{
				printf("cd: HOME not set\n");
				return ;
			}
		}
		else
			path = *args;
		err_n = chdir(path);
		if (err_n)
			ft_error(err_n);
	}
	else
		printf("too many arguments\n");
}

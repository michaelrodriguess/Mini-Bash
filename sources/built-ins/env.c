/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:33:05 by microdri          #+#    #+#             */
/*   Updated: 2023/04/10 16:46:31 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_copy_env(char **env)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	j = 0;
	copy = malloc(ft_size_matriz(env) * sizeof(char *));
	if (!copy)
		return (NULL);
	while (env[i])
	{
		copy[j] = ft_strdup(env[i]);
		i++;
		j++;
	}
	copy[j] = NULL;
	return (copy);
}

void	ft_env(char **copy_env, int fd_out)
{
	int	index;

	index = 0;
	while (copy_env[index])
	{
		ft_putstr_fd(copy_env[index], fd_out);
		write(fd_out, "\n", 1);
		index++;
	}
	g_var_global = 0;
}

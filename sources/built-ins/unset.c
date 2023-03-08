/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:24:01 by microdri          #+#    #+#             */
/*   Updated: 2023/03/08 20:30:43 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **new_env(t_data_shell *data_shell)
{
	int i;
	int j;
	char **new_environ;

	i = 0;
	j = 0;
	new_environ = malloc((ft_size_matriz(data_shell->copy_env) - 1) * sizeof(char *));
	if (!new_environ)
		return (NULL);	
	while(data_shell->copy_env[i])
	{
		if (ft_strcmp(*data_shell->args, data_shell->copy_env[i]) == 0)
			i++;
		else
		{
			new_environ[j] = ft_strdup(data_shell->copy_env[i]);
			j++;
			i++;
		}
	}
	new_environ[j] = NULL;
	return (new_environ);
}


void	ft_unset(t_data_shell *data_shell)
{
	int i;
	int j;
	char **temp;

	i = 0;
	j = 0;
	while (data_shell->copy_env[i] != NULL)
	{
		if (ft_strcmp(*data_shell->args, data_shell->copy_env[i]) == 0)
			temp = new_env(data_shell);
		i++;
	}
	free_copy_env(data_shell);
	i = 0;
	data_shell->copy_env = temp;
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:24:01 by microdri          #+#    #+#             */
/*   Updated: 2023/03/09 16:22:08 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int has_equal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

char **new_env(t_data_shell *data_shell, int current_args_i)
{
	int i;
	int j;
	int	env_size;
	char **new_environ;

	i = 0;
	j = 0;
	new_environ = malloc((ft_size_matriz(data_shell->copy_env) - 1) * sizeof(char *));
	if (!new_environ)
		return (NULL);	
	while(data_shell->copy_env[i])
	{
		env_size = ft_strchri(data_shell->copy_env[i], '=') - 1;
		if ((int)ft_strlen(data_shell->args[current_args_i]) == env_size &&
			ft_strncmp(data_shell->args[current_args_i], data_shell->copy_env[i], env_size) == 0)
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
	int	env_size;
	char **temp;

	j = 0;
	if (data_shell->args == NULL)
		return ;
	while (data_shell->args[j])
	{
		if (ft_strcmp("_", data_shell->args[j]) == 0)
			j++;
		else
		{
		if (has_equal(data_shell->args[j]) == 0)
			printf("microtano: unset: `%s': not a valid identifier\n", data_shell->args[j++]);
		i = 0;
		while (data_shell->copy_env[i] != NULL && data_shell->args[j] != NULL)
		{
			env_size = ft_strchri(data_shell->copy_env[i], '=') - 1;
			if ((int)ft_strlen(data_shell->args[j]) == env_size &&
				ft_strncmp(data_shell->args[j], data_shell->copy_env[i], env_size) == 0)
			{
				temp = new_env(data_shell, j);
				free_copy_env(data_shell);
				data_shell->copy_env = temp;
			}
			i++;
		}
		j++;
		}
	}
}


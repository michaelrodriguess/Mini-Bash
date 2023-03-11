/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:51:10 by microdri          #+#    #+#             */
/*   Updated: 2023/03/11 16:26:56 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// caso o nome da variavel de ambiente ja exista atualizaremos o valor dela na lnha 40;
// senao cria uma copia da env com a variavel nova!

char	**update_env(t_data_shell *data_shell, int current_args_i)
{
	int i;
	int j;
	int env_until_equal;
	int	args_until_equal;
	char **new_env;

	new_env = malloc(ft_size_matriz(data_shell->copy_env) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (data_shell->copy_env[i])
	{
		args_until_equal = ft_strchri(data_shell->args[current_args_i], '=');
		env_until_equal = ft_strchri(data_shell->copy_env[i], '=');
		if (args_until_equal == env_until_equal &&
				ft_strncmp(data_shell->args[current_args_i], data_shell->copy_env[i], env_until_equal) == 0)
			new_env[j] = ft_strdup(data_shell->args[current_args_i]);
		else
			new_env[j] = ft_strdup(data_shell->copy_env[i]);
		j++;
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

char **add_new_env(t_data_shell *data_shell, int current_args_i)
{
	int i;
	char **new_env;

	new_env = malloc((ft_size_matriz(data_shell->copy_env) + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while(data_shell->copy_env[i])
	{
		new_env[i] = ft_strdup(data_shell->copy_env[i]);
		i++;
	}
	new_env[i] = ft_strdup(data_shell->args[current_args_i]);
	i++;
	new_env[i] = NULL;
	return (new_env);
}


void	ft_export(t_data_shell *data_shell)
{
	int	i;
	int	j;
	int until_equal;
	int flag_is_equal;
	char **temp;

	if (data_shell->args == NULL)
		return ;
	i = 0;
	while (data_shell->args[i])
	{
		if (has_equal(data_shell->args[i]) == 0)
		{
			j = 0;
			flag_is_equal = 0;
			while (data_shell->copy_env[j] && data_shell->args[i] != NULL)
			{
				until_equal = ft_strchri(data_shell->copy_env[j], '=');
				if (strncmp(data_shell->args[i], data_shell->copy_env[j], until_equal) == 0)
				{
					temp = update_env(data_shell, i);
					flag_is_equal = 1;
					free_copy_env(data_shell);
					data_shell->copy_env = temp;
					break ;
				}
				j++;
			}
			if (flag_is_equal == 0)
			{
				temp = add_new_env(data_shell, i);
				free_copy_env(data_shell);
				data_shell->copy_env = temp;
			}
		}
		i++;
	}
}

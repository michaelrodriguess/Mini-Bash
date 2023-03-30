/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:51:10 by microdri          #+#    #+#             */
/*   Updated: 2023/03/29 14:21:34 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char	**update_env(t_data_shell *data_shell, int current_args_i)
{
	int		i;
	int		env_until_equal;
	int		args_until_equal;
	char	**new_env;

	new_env = malloc(ft_size_matriz(data_shell->copy_env) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (data_shell->copy_env[i])
	{
		args_until_equal = ft_strchri(data_shell->sentence_list->args[current_args_i], '=');
		env_until_equal = ft_strchri(data_shell->copy_env[i], '=');
		if (args_until_equal == env_until_equal
			&& ft_strncmp(data_shell->sentence_list->args[current_args_i],
				data_shell->copy_env[i], env_until_equal) == 0)
			new_env[i] = ft_strdup(data_shell->sentence_list->args[current_args_i]);
		else
			new_env[i] = ft_strdup(data_shell->copy_env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**add_new_env(t_data_shell *data_shell, int current_args_i)
{
	int		i;
	char	**new_env;

	new_env = malloc((ft_size_matriz(data_shell->copy_env) + 1)
			* sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (data_shell->copy_env[i])
	{
		new_env[i] = ft_strdup(data_shell->copy_env[i]);
		i++;
	}
	new_env[i] = ft_strdup(data_shell->sentence_list->args[current_args_i]);
	i++;
	new_env[i] = NULL;
	return (new_env);
}

int	exec_export(t_data_shell *data_shell, int i)
{
	int		j;
	int		until_equal;
	char	**temp;

	j = 0;
	while (data_shell->copy_env[j] && data_shell->sentence_list->args[i] != NULL)
	{
		until_equal = ft_strchri(data_shell->copy_env[j], '=');
		if (!strncmp(data_shell->sentence_list->args[i], data_shell->copy_env[j], until_equal))
		{
			temp = update_env(data_shell, i);
			free_copy_env(data_shell);
			data_shell->copy_env = temp;
			return (1);
		}
		j++;
	}
	return (0);
}

void	ft_export(t_data_shell *data_shell)
{
	int		i;
	char	**temp;

	if (data_shell->sentence_list->args == NULL)
		return ;
	i = 0;
	while (data_shell->sentence_list->args[i])
	{
		if (is_name_valid(data_shell->sentence_list->args[i]) == 0)
			message_error("microtano: export: not a valid identifier\n", 1);
		else if (has_equal(data_shell->sentence_list->args[i]) == 0)
		{
			if (exec_export(data_shell, i) == 0)
			{
				temp = add_new_env(data_shell, i);
				free_copy_env(data_shell);
				data_shell->copy_env = temp;
			}
		}
		i++;
	}
}

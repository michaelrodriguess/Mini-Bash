/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:24:01 by microdri          #+#    #+#             */
/*   Updated: 2023/04/07 17:31:19 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**new_env(t_data_shell	*shell, int cur_args_i)
{
	int		i;
	int		j;
	int		env_sz;
	char	**new_environ;

	i = 0;
	j = 0;
	new_environ = malloc((ft_size_matriz(shell->copy_env) - 1)
			* sizeof(char *));
	if (!new_environ)
		return (NULL);
	while (shell->copy_env[i])
	{
		env_sz = ft_strchri(shell->copy_env[i], '=') - 1;
		if ((int)ft_strlen(shell->sentence_list->args[cur_args_i]) == env_sz
			&& ft_strncmp(shell->sentence_list->args[cur_args_i],
				shell->copy_env[i], env_sz) == 0)
			i++;
		else
			new_environ[j++] = ft_strdup(shell->copy_env[i++]);
	}
	new_environ[j] = NULL;
	return (new_environ);
}

void	exec_unset(t_data_shell *shell, int j)
{
	int		i;
	int		env_until_equal;
	char	**temp;

	i = 0;
	while (shell->copy_env[i] && shell->sentence_list->args[j])
	{
		env_until_equal = ft_strchri(shell->copy_env[i], '=') - 1;
		if ((int)ft_strlen(shell->sentence_list->args[j]) == env_until_equal
			&& ft_strncmp(shell->sentence_list->args[j],
				shell->copy_env[i], env_until_equal) == 0)
		{
			temp = new_env(shell, j);
			free_copy_env(shell->copy_env);
			shell->copy_env = temp;
		}
		else
			i++;
	}
	return ;
}

void	ft_unset(t_data_shell *data_shell)
{
	int		j;

	j = 0;
	if (data_shell->sentence_list->args == NULL)
		return ;
	while (data_shell->sentence_list->args[j])
	{
		if (data_shell->sentence_list->args[j] == NULL)
			break ;
		if (has_equal(data_shell->sentence_list->args[j]) == 0
			|| is_name_valid(data_shell->sentence_list->args[j]) == 0)
			message_error("microtano: unset: not a valid identifier", 1);
		if (data_shell->sentence_list->args[j] == NULL)
			break ;
		else
		{
			if (ft_strcmp("_", &data_shell->sentence_list->args[j][0]) != 0)
				exec_unset(data_shell, j);
		}
		j++;
	}
}

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

char	**update_env(char **input, char **env, int current_args_i)
{
	int		i;
	int		env_until_equal;
	int		args_until_equal;
	char	**new_env;

	new_env = malloc(ft_size_matriz(env) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		args_until_equal = ft_strchri(input[current_args_i], '=');
		env_until_equal = ft_strchri(env[i], '=');
		if (args_until_equal == env_until_equal
			&& ft_strncmp(input[current_args_i],
				env[i], env_until_equal) == 0)
			new_env[i] = ft_strdup(input[current_args_i]);
		else
			new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**add_new_env(char **input, char **env, int current_args_i)
{
	int		i;
	char	**new_env;

	new_env = malloc((ft_size_matriz(env) + 1)
			* sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(input[current_args_i]);
	i++;
	new_env[i] = NULL;
	return (new_env);
}

int	exec_export(char **input, char ***env, int i)
{
	int		j;
	int		until_equal;
	char	**temp;

	j = 0;
	while ((*env)[j] && input[i] != NULL)
	{
		until_equal = ft_strchri((*env)[j], '=');
		if (!strncmp(input[i], (*env)[j], until_equal))
		{
			temp = update_env(input, *env, i);
			free_copy_env(*env);
			*env = temp;
			return (1);
		}
		j++;
	}
	return (0);
}

void	ft_export(char **input, char ***env)
{
	int		i;
	char	**temp;

	if (input == NULL)
		return ;
	i = 0;
	while (input[i])
	{
		if (is_name_valid(input[i]) == 0)
			printf("microtano: export: %s: not a valida identifier\n",
				input[i]);
		else if (has_equal(input[i]) == 0)
		{
			if (exec_export(input, env, i) == 0)
			{
				temp = add_new_env(input, *env, i);
				free_copy_env(*env);
				*env = temp;
			}
		}
		i++;
	}
}

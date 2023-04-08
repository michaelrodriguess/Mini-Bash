/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envvar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:22:42 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/29 16:53:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	expand(char **env_var, char **env)
{
	char	*temp;
	int		i;
	int		len;

	i = 0;
	temp = ft_substr(env[0], 0, ft_strchri(env[0], '=') - 1);
	while (env[i] && ft_strcmp(temp, &((*env_var)[1])))
	{
		i++;
		free(temp);
		if (env[i])
			temp = ft_substr(env[i], 0, ft_strchri(env[i], '=') - 1);
	}
	if (!env[i])
	{
		free(env_var[0]);
		env_var[0] = ft_strdup("");
	}
	else
	{
		free(temp);
		len = ft_strlen(env[i]) - ft_strchri(env[i], '=') + 1;
		free(env_var[0]);
		env_var[0] = ft_substr(env[i], ft_strchri(env[i], '='), len);
	}
}

void	insert_envvar(char **str, char *env_var, int start, int end)
{
	char	*temp;

	temp = *str;
	*str = remove_substr(*str, start, end - 1);
	free (temp);
	temp = *str;
	*str = insert_substr(*str, env_var, start);
	free (temp);
}

void	expand_str(char **str, char **env)
{
	char	*env_var;
	int		i;
	int		start_envvar;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && ((*str)[i + 1] == '_'
			|| ft_isalnum((*str)[i + 1])))
		{
			start_envvar = i;
			i++;
			while (ft_isalnum((*str)[i]) || (*str)[i] == '_')
				i++;
			env_var = ft_substr(*str, start_envvar, i - start_envvar);
			expand(&env_var, env);
			insert_envvar(str, env_var, start_envvar, i);
			i = start_envvar + ft_strlen(env_var);
			free (env_var);
		}
		else
			i++;
	}
}

char	*cat_exitstatus(char **arg, char *parsed_arg)
{
	char	*expanded_str;
	char	*temp;

	temp = ft_itoa(g_var_global);
	expanded_str = ft_strjoin(parsed_arg, temp);
	free(temp);
	*arg += 2;
	return (expanded_str);
}

char	*cat_envvar(char **arg, char *parsed_arg, char **env)
{
	int		i;
	char	*env_var;
	char	*temp;

	i = 1;
	while (ft_isalnum((*arg)[i]) || (*arg)[i] == '_')
		i++;
	env_var = ft_substr(*arg, 0, i);
	expand_str(&env_var, env);
	*arg += i;
	if (ft_strlen(env_var) == 0 && ft_strlen(parsed_arg) == 0)
	{
		free(env_var);
		return (NULL);
	}
	else if (parsed_arg)
	{
		temp = env_var;
		env_var = ft_strjoin(parsed_arg, env_var);
		free(temp);
	}
	return (env_var);
}

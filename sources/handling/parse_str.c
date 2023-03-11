/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:47:39 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/09 17:12:51 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			free (env_var);
			i = 0;
		}
		else
			i++;
	}
}

char	*quote(char	**arg, char *parsed_arg, char **env)
{
	int		i;
	char	*ret;
	char	*temp;
	char	quote;

	i = 0;
	quote = **arg;
	while ((*arg)[i + 1] != quote && (*arg)[i + 1])
		i++;
	temp = ft_substr((*arg), 1, i);
	if (quote == '\"' && ft_strchri(temp, '$'))
		expand_str(&temp, env);
	ret = ft_strjoin(parsed_arg, temp);
	free(temp);
	if ((*arg)[i + 1])
		i++;
	(*arg) += i + 1;
	return (ret);
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

char	*parse_arg(char *arg, char **env)
{
	char	*parsed_arg;
	char	*temp;

	parsed_arg = ft_strdup("");
	while (*arg)
	{
		if (!parsed_arg)
			parsed_arg = ft_strdup("");
		temp = parsed_arg;
		if (*arg == '\"' || *arg == '\'')
			parsed_arg = quote(&arg, parsed_arg, env);
		else if (*arg == '$' && (arg[1] == '_' || ft_isalnum(arg[1])))
			parsed_arg = cat_envvar(&arg, parsed_arg, env);
		else
		{
			parsed_arg = strjoinchr(parsed_arg, *arg);
			arg++;
		}
		free(temp);
	}
	return (parsed_arg);
}

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

/*void	expand(char **env_var, char **env)
{
	char	*temp;
	int		i;
	int		len;

	i = 0;
	temp = ft_substr(env[0], 0, ft_strchri(env[0], '=') - 1);
	while (ft_strcmp(temp, &((*env_var)[1])) && env[i])
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
		len = ft_strlen(env[i]) - ft_strchri(env[i], '=') + 1;
		free(env_var[0]);
		env_var[0] = ft_substr(env[i], ft_strchri(env[i], '='), len);
	}
}*/

/*char **split_env_var(char *str)
{
	int		i;
	char	**array;

	array = malloc(sizeof(char *) * 2);
	i = 1;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (i == (int) (ft_strlen(str) - 1))
	{
		array[0] = str;
		array[1] = NULL;
	}
	else
	{
		array[0] = ft_substr(str, 1, i);
		array[1] = ft_substr(str, i, ft_strlen(str) - i);
	}
	return (array);	
}

char	*expand_env_var(t_token *tok_lst, char **env)
{
	char	**array;
	char	*arg;

	//(void) *tok_lst;
	(void) *env;
	arg = NULL;
	array = split_env_var(tok_lst->str);
	if (array[0] && array[1])
	{
		arg = ft_strjoin(array[0], array[1]);
		free(array[0]);
		free(array[1]);
	}
	else if (array[0])
		arg = ft_strdup("test");
	else if (array[1])
		arg = array[1];
	free(array);
	return(arg);
}

char	*add_env_var(t_token **tok_lst, char **env)
{
	char	*arg;
	char	*temp;

	(void) *env;
	if (strlen((*tok_lst)->str) == 1)
	{
		arg = (*tok_lst)->str;
		*tok_lst = (*tok_lst)->next;
		return (arg);
	}
	else
	{
		temp = (*tok_lst)->str;
		arg = expand_env_var(*tok_lst, env);
		(*tok_lst)->str = arg;
		free(temp);
		*tok_lst = (*tok_lst)->next;
		return (arg);
	}
}*/

/*char	*double_quote(char	**arg, char *parsed_arg)
{
	int		i;
	char	*ret;
	char	*temp;

	i = 0;
	while((*arg)[i + 1] != '\"' && (*arg)[i + 1])
		i++;
	temp = ft_substr((*arg), 1, i);
	ret = ft_strjoin(parsed_arg, temp);
	free(temp);
	if ((*arg)[i + 1])
		i++;
	(*arg) += i + 1;
	return (ret);
}*/

void	expand(char **env_var, char **env)
{
	char	*temp;
	int		i;
	int		len;

	i = 0;
	temp = ft_substr(env[0], 0, ft_strchri(env[0], '=') - 1);
	while (ft_strcmp(temp, &((*env_var)[1])) && env[i])// not pass the $ and simplify the code
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

void	expand_str(char **str, char **env)
{
	char	*ret;
	char	*env_var;
	char	*temp;
	int		i;
	int		start_envvar;

	ret = *str;
	i = 0;
	while (ret[i])
	{
		if (ret[i] == '$' && (ret[i + 1] == '_' || ft_isalnum(ret[i + 1])))
		{
			start_envvar = i;
			i++;
			while (ft_isalnum(ret[i]) || ret[i] == '_')
				i++;
			env_var = ft_substr(ret, start_envvar, i - start_envvar);
			expand(&env_var, env);
			temp = ret;
			ret = remove_substr(ret, start_envvar, i);
			free (temp);
			temp = ret;
			ret = insert_substr(ret, env_var, start_envvar);
			free (temp);
			free (env_var);
			*str = ret;
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
	while((*arg)[i + 1] != quote && (*arg)[i + 1])
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
	*arg += i + 1;
	temp = env_var;
	env_var = ft_strjoin(parsed_arg, env_var);
	free(temp);
	return (env_var);
}

char	*parse_arg(char *arg, char **env)
{
	char	*parsed_arg;
	char	*temp;

	parsed_arg = ft_strdup("");
	while (*arg)
	{
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
	return(parsed_arg);
}

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
}

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

void	expand_envvar(char **env_str, char **env)
{
	char	*ret;
	char	*pre_suffix;
	char	*env_var;
	char	*temp;
	int		i;

	ret = *env_str;
	i = 0;
	while (ret[i])
	{
		if (ret[i] == '$' && (ret[i + 1] == '_' || ft_isalnum(ret[i + 1])));
		{
			temp = ret;
			pre_suffix = ft_substr(ret, 0, i);
			ret += i;
			free(temp);
			env_var = (&ret, env); 
				//ft_substr(ret, i, ft_strlen(&ret[i]));
		}
	}
}

char	*quote(char	**arg, char *parsed_arg)
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
	if (quote == '\"' && ft_strchri(temp, '$')
		expand_envvar(&temp);
	ret = ft_strjoin(parsed_arg, temp);
	free(temp);
	if ((*arg)[i + 1])
		i++;
	(*arg) += i + 1;
	return (ret);
}

char	*parse_arg(char *arg)
{
	char	*parsed_arg;
	char	*temp;

	parsed_arg = ft_strdup("");
	while (*arg)
	{
		temp = parsed_arg;
		if (*arg == '\"' || *arg == '\'')
			parsed_arg = quote(&arg, parsed_arg);
//		else if (*arg == '\'')
//			parsed_arg = single_quote(&arg, parsed_arg);
		else
		{
			parsed_arg = strjoinchr(parsed_arg, *arg);
			arg++;
		}
		free(temp);
	}
	return(parsed_arg);
}

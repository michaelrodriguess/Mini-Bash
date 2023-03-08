//HEADER

#include "../../includes/minishell.h"

/*void	expand_envvar(char **env_var, char **env)
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

char **split_env_var(char *str)
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
}

char	*double_quote(char	**arg, char *parsed_arg)
{
	int		i;
	char	*ret;

	i = 1;
	while((*arg)[i] != '\"' && (*arg)[i])
		i++;
	return ("");
}

char	*strjoinchr(char *str, char chr)
{
	char	*ret;
	int		i;

	if (!str)
		return (NULL);
	ret = malloc(sizeof(char) * ft_strlen(str) + 2);
	i = 0;
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = chr;
	ret[i + 1] = 0;
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
		if (*arg == '\"')
			parsed_arg = double_quote(&arg, parsed_arg);
		else
		{
			parsed_arg = strjoinchr(parsed_arg, *arg);
			arg++;
		}
		free(temp);
	}
	return(parsed_arg);
}

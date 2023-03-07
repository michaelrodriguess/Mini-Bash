/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:20:34 by microdri          #+#    #+#             */
/*   Updated: 2023/03/06 18:56:37 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *command)
{
	if (!ft_strcmp(command, "echo") || !ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "exit") || !ft_strcmp(command, "pwd")
		|| !ft_strcmp(command, "env") || !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset"))
		return (1);
	else
		return (0);
}

int	execute_builtins(char *command, char **args, char **env)
{	
	(void) *env;
	if (!ft_strcmp(command, "echo"))
		ft_echo(args);
	if (!ft_strcmp(command, "pwd"))
		ft_pwd();
	if (!ft_strcmp(command, "cd"))
		ft_cd(args);
	return (0);
}

char *add_arg(t_token **token_lst)
{
	char	*arg;

	arg = NULL;
	if (*token_lst)
	{
		arg = (*token_lst)->str;
		*token_lst = (*token_lst)->next;
	}
	return (arg);
}

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
}



char	*add_env_var(t_token **token_lst, char **env)
{
	char	*temp;
	char	**array;
//	char	expand_var;

	if ((*token_lst)->str != NULL)
	{
		if (ft_strlen((*token_lst)->str) == 1)
		{
			*token_lst = (*token_lst)->next;
			return ((*token_lst)->str);
		}
		array = split_envvar((*token_lst)->str);
		expand_envvar(array, env);
		temp = (*token_lst)->str;
		(*token_lst)->str = ft_strjoin(array[0], array[1]);
		*token_lst = (*token_lst)->next;
		free(temp);
		free(array[0]);
		free(array[1]);
		free(array);
	}
	return ((*token_lst)->str);
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

void	parser_builtin(t_data_shell *data_shell)
{
	char	**args;
	char	*command;
	int		size;
	int		index;

	index = 0;
	command = data_shell->tok_lst->str;
	data_shell->tok_lst = data_shell->tok_lst->next;
	args = NULL;
	if (data_shell->tok_lst != NULL)
	{
		size = ft_toksize_w(data_shell->tok_lst);
		args = malloc((size + 1) * sizeof(char *));
		if (!args)
			printf("Error in parser built-in malloc.\n");
		while (data_shell->tok_lst != NULL)
		{
			if (data_shell->tok_lst->type == 0)
				args[index] = add_arg(&data_shell->tok_lst);
			else if (data_shell->tok_lst->type == 8)
				args[index] = add_env_var(&data_shell->tok_lst, data_shell->env);
			if (args[index]) //if NULL than i wont increase index and save the next arg in that same position
				index++;
		}
		args[index] = NULL; //will segfault if args[index] is already NULL? Yes, probably.
	}
	execute_builtins(command, args, data_shell->env);
	free(args);
}


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

char	*expand_envvar(t_token *token_lst, char **env)
{
	char	*temp;
	int		i;
	int		len;

	i = 0;
	temp = ft_substr(env[0], 0, ft_strchri(env[0], '=') - 1);
	while (ft_strcmp(temp, &(token_lst->str[1])) && env[i])
	{
		i++;
		free(temp);
		if (env[i])
			temp = ft_substr(env[i], 0, ft_strchri(env[i], '=') - 1);
	}
	temp = token_lst->str;
	if (!env[i])
		token_lst->str = &(token_lst->str[1]);
	else
	{
		len = ft_strlen(env[i]) - ft_strchri(env[i], '=') + 1;
		token_lst->str = ft_substr(env[i], ft_strchri(env[i], '='), len);
	}
	free(temp);
	return (token_lst->str);
}

char	*add_env_var(t_token **token_lst, char **env)
{
	char *arg;

	arg = NULL;
	if ((*token_lst)->str != NULL)
	{
		arg = (*token_lst)->str;
		if (ft_strlen(arg) == 1)
		{
			*token_lst = (*token_lst)->next;
			return (arg);
		}
		arg = expand_envvar(*token_lst, env);
		*token_lst = (*token_lst)->next;
	}
	return (arg);
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
			index++;
		}
		args[index] = NULL;
	}
	execute_builtins(command, args, data_shell->env);
	free(args);
}


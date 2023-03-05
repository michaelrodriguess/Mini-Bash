/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:20:34 by microdri          #+#    #+#             */
/*   Updated: 2023/03/02 18:32:41 by microdri         ###   ########.fr       */
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

int	execute_builtins(char *command, char **args)
{	
	if (!ft_strcmp(command, "echo"))
		ft_echo(args);
	if (!ft_strcmp(command, "pwd"))
		ft_pwd();
	if (!ft_strcmp(command, "cd"))
		ft_cd(args);
	return(0);
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

/*
char *add_env_var(t_token **token_lst)
{
	char *arg;

	arg = NULL;
	if ( )	{
		
	}


}
*/

void parser_builtin(t_token *token_lst)
{
	char	**args;
	char	*command;
	int		size;
	int		index;

	index = 0;
	command = token_lst->str;
	token_lst = token_lst->next;
	args = NULL;
	if (token_lst != NULL)
	{
		size = ft_toksize_w(token_lst);
		args = malloc((size + 1) * sizeof(char *));
		if (!args)
			printf("Error in parser built-in malloc.\n");
		while (token_lst != NULL)
		{
			if (token_lst->type == 0)
				args[index] = add_arg(&token_lst);
			else if (token_lst->type == 8)
				args[index] = add_arg(&token_lst); //call add_env_var instead
			index++;
		}
		args[index] = NULL;
	}
	execute_builtins(command, args);
}


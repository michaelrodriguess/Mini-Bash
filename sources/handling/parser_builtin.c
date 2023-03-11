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

int	execute_builtins(char *command, t_data_shell *data_shell)
{	
	if (!ft_strcmp(command, "echo"))
		ft_echo(data_shell->args);
	if (!ft_strcmp(command, "pwd"))
		ft_pwd();
	if (!ft_strcmp(command, "cd"))
		ft_cd(data_shell->args);
	return (0);
}

char	*add_arg(t_data_shell *data_shell)
{
	char	*arg;
	char	*temp;

	arg = NULL;
	if (data_shell->tok_lst)
	{
		arg = data_shell->tok_lst->str;
		if (ft_strchri(arg, '$') || ft_strchri(arg, '\'')
			|| ft_strchri(arg, '\"'))
		{
			temp = arg;
			arg = parse_arg(arg, data_shell->env);
			free(temp);
			data_shell->tok_lst->str = arg;
		}
		data_shell->tok_lst = data_shell->tok_lst->next;
	}
	return (arg);
}

void	parser_builtin(t_data_shell *data_shell)
{
	char	*command;
	int		size;
	int		index;

	index = 0;
	command = data_shell->tok_lst->str;
	data_shell->tok_lst = data_shell->tok_lst->next;
	data_shell->args = NULL;
	if (data_shell->tok_lst != NULL)
	{
		size = ft_toksize_w(data_shell->tok_lst);
		data_shell->args = malloc((size + 1) * sizeof(char *));
		if (!data_shell->args)
			printf("Error in parser built-in malloc.\n");
		while (data_shell->tok_lst != NULL)
		{
			if (data_shell->tok_lst->type == 0)
				data_shell->args[index] = add_arg(data_shell);
			if (data_shell->args[index])
				index++;
		}
		data_shell->args[index] = NULL;
	}
	execute_builtins(command, data_shell);
	free(data_shell->args);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:15:21 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/16 11:54:41 by fcaetano         ###   ########.fr       */
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

int	execute_builtins(t_data_shell *data_shell)
{
	char	*command;

	command = data_shell->sentence_list->args[0];
	if (!ft_strcmp(command, "echo")) //printar quebra de linha quando o input for echo sem argumentos ou flags
		ft_echo(&(data_shell->sentence_list->args[1]));
	if (!ft_strcmp(command, "pwd")) //atualizar $PWD e $OLDPWD
		ft_pwd();
	if (!ft_strcmp(command, "cd")) // error with only cd HOME at env[4]
		ft_cd(&(data_shell->sentence_list->args[1]), data_shell->copy_env);
	if (!ft_strcmp(command, "exit"))
		ft_exit(&(data_shell->sentence_list->args[1]));
	if (!ft_strcmp(command, "env"))
		ft_env(data_shell->copy_env);
	if (!ft_strcmp(command, "unset"))
		ft_unset(data_shell);
	if (!ft_strcmp(command, "export"))
		ft_export(data_shell);
	return (0);
}

void	execute_cmd(t_data_shell *data_shell)
{
	int	pid;
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("Error with Fork", 2);
	if (pid == 0 && execve(data_shell->sentence_list->args[0], data_shell->sentence_list->args, data_shell->copy_env) == -1)
		ft_putstr_fd("Error with second command", 2);
	else if (pid !=  0)
		wait(&pid);
}

void	verify_and_exec(t_data_shell *data_shell)
{
	char *command;

	if (!data_shell->sentence_list)
		return ;
	if (data_shell->sentence_list->args == NULL)
		printf("cmd not found: depois volta aqui\n");
	command = data_shell->sentence_list->args[0];
	if (is_builtin(command) == 1)
	 	execute_builtins(data_shell);
	else
		execute_cmd(data_shell);
}

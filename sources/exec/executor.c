/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:15:21 by fcaetano          #+#    #+#             */
/*   Updated: 2023/04/11 12:15:39 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtins(t_data_shell *data_shell)
{
	char	*command;

	command = data_shell->sentence_list->args[0];
	if (!ft_strcmp(command, "echo"))
		ft_echo(&(data_shell->sentence_list->args[1]),
			data_shell->sentence_list->fd_out);
	if (!ft_strcmp(command, "pwd"))
		ft_pwd(data_shell->copy_env);
	if (!ft_strcmp(command, "cd"))
		ft_cd(&(data_shell->sentence_list->args[1]), &data_shell->copy_env);
	if (!ft_strcmp(command, "exit"))
		ft_exit(&(data_shell->sentence_list->args[1]));
	if (!ft_strcmp(command, "env")
		&& data_shell->sentence_list->args[1] == NULL)
		ft_env(data_shell->copy_env, data_shell->sentence_list->fd_out);
	if (!ft_strcmp(command, "unset"))
		ft_unset(data_shell);
	if (!ft_strcmp(command, "export"))
		ft_export(&(data_shell->sentence_list->args[1]), &data_shell->copy_env);
	return (0);
}

void	exec_fork(t_data_shell *data_shell)
{
	child_sig_def();
	if (data_shell->sentence_list->fd_in != 0)
		dup2(data_shell->sentence_list->fd_in, 0);
	if (data_shell->sentence_list->fd_out != 1)
		dup2(data_shell->sentence_list->fd_out, 1);
	execve(data_shell->sentence_list->args[0], data_shell->sentence_list->args,
		data_shell->copy_env);
}

void	execute_cmd(t_data_shell *shell)
{
	int	pid;
	int	status;

	if (shell->sentence_list->fd_out == -1 || shell->sentence_list->fd_in == -1)
		return ;
	if (shell->sentence_list->args == NULL)
		message_error("microtano: command not found", 127);
	else if (is_builtin(shell->sentence_list->args[0]) == 1)
		execute_builtins(shell);
	else
	{
		pid = fork();
		if (pid == -1)
			message_error("Error with Fork", -1);
		if (pid == 0)
			exec_fork(shell);
		if (pid != 0)
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				g_var_global = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
				g_var_global = 128 + WTERMSIG(status);
		}
	}
}

void	verify_and_exec(t_data_shell *data_shell)
{
	data_shell->number_of_sentence = (count_pipes(data_shell->tok_lst) + 1);
	if (!data_shell->sentence_list)
		return ;
	if (data_shell->number_of_sentence == 1)
		execute_cmd(data_shell);
	else if (data_shell->number_of_sentence > 1)
		execute_pipeline(data_shell);
}

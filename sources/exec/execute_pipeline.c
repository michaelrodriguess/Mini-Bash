/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:34:26 by microdri          #+#    #+#             */
/*   Updated: 2023/04/10 17:45:12 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_pipeline(t_data_shell *data_shell)
{
	config_pipes(data_shell);
	exec_pipes(data_shell);
}

void	do_fork(t_data_shell *data_shell)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		message_error("Error with Fork", -1);
	if (pid == 0)
		exec_sentence(data_shell);
	data_shell->sentence_list->pid = pid;
}

void	exec_pipes(t_data_shell *data_shell)
{
	t_sentence	*head;
	int			n_sentence;

	head = data_shell->sentence_list;
	n_sentence = 0;
	while (n_sentence < data_shell->number_of_sentence)
	{
		data_shell->sentence_list->pid = -1;
		if (data_shell->sentence_list->args == NULL)
			message_error("microtano: command not found", 127);
		else if (data_shell->sentence_list->fd_out != -1
				&& data_shell->sentence_list->fd_in != -1)
			do_fork(data_shell);
		n_sentence++;
		data_shell->sentence_list = data_shell->sentence_list->next;
	}
	data_shell->sentence_list = head;
	close_pipes(data_shell);
	wait_sentences(data_shell);
}

void	exec_sentence(t_data_shell *data_shell)
{
	if (data_shell->sentence_list->fd_in != 0)
		dup2(data_shell->sentence_list->fd_in, 0);
	if (data_shell->sentence_list->fd_in != 1)
		dup2(data_shell->sentence_list->fd_out, 1);
	close_pipes(data_shell);
	if (is_builtin(data_shell->sentence_list->args[0]))
	{
		data_shell->sentence_list->fd_out = 1;
		execute_builtins(data_shell);
		clear_memory(*data_shell, EXIT_EXEC);
		exit(1);
	}
	else
	{
		if (data_shell->fd_redis)
			free(data_shell->fd_redis);
		if (execve(data_shell->sentence_list->args[0],
				data_shell->sentence_list->args, data_shell->copy_env) == -1)
			message_error("Error with exec command", -1);
	}
}

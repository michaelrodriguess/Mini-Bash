/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:42:30 by microdri          #+#    #+#             */
/*   Updated: 2023/03/30 11:02:29 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	config_pipes(t_data_shell *shell)
{
	int			pipefd[2];
	int			current_pipe;
	t_sentence	*head;

	head = shell->sentence_list;
	shell->n_pipes = count_pipes(shell->tok_lst);
	shell->fd_pipes = malloc(sizeof(int) * 2 * shell->n_pipes);
	current_pipe = 0;
	while (shell->n_pipes > current_pipe)
	{
		if (pipe(pipefd) == -1)
			message_error("Error with Pipe", -1);
		shell->fd_pipes[current_pipe * 2] = pipefd[0];
		shell->fd_pipes[(current_pipe * 2) + 1] = pipefd[1];
		if (shell->sentence_list->prev != NULL)
			shell->sentence_list->fd_in = shell->sentence_list->prev->fd_in;
		else
			shell->sentence_list->fd_in = pipefd[0];
		shell->sentence_list->fd_out = pipefd[1];
		shell->sentence_list = shell->sentence_list->next;
		current_pipe++;
	}
	shell->sentence_list->fd_in = pipefd[0];
	shell->sentence_list = head;
}

void	wait_sentences(t_data_shell *data_shell)
{
	t_sentence	*head;
	int			status;

	head = data_shell->sentence_list;
	while (data_shell->sentence_list)
	{
		waitpid(data_shell->sentence_list->pid, &status, 0);
		data_shell->sentence_list = data_shell->sentence_list->next;
	}
	data_shell->sentence_list = head;
}

void	close_pipes(t_data_shell *data_shell)
{
	int	current_pipe;

	current_pipe = 0;
	while (current_pipe < data_shell->n_pipes)
	{
		close(data_shell->fd_pipes[current_pipe * 2]);
		close(data_shell->fd_pipes[(current_pipe * 2) + 1]);
		current_pipe++;
	}
}

void	config_forks(t_data_shell *data_shell)
{
	t_sentence	*head;
	int			pid;
	int			n_sentence;

	head = data_shell->sentence_list;
	n_sentence = 0;
	while (n_sentence < data_shell->number_of_sentence)
	{
		pid = fork();
		if (pid == -1)
			message_error("Error with Fork", -1);
		if (pid == 0)
		{
			exec_pipes(data_shell, n_sentence);
		}
		data_shell->sentence_list->pid = pid;
		n_sentence++;
		data_shell->sentence_list = data_shell->sentence_list->next;
	}
	data_shell->sentence_list = head;
	close_pipes(data_shell);
	wait_sentences(data_shell);
}

void	exec_pipes(t_data_shell *data_shell, int n_sentence)
{
	if (n_sentence != 0)
		dup2(data_shell->sentence_list->fd_in, 0);
	if (n_sentence != (data_shell->number_of_sentence - 1))
		dup2(data_shell->sentence_list->fd_out, 1);
	close_pipes(data_shell);
	if (is_builtin(data_shell->sentence_list->args[0]))
	{
		execute_builtins(data_shell);
	//	close(0);
	//	close(1);
		clear_history();
		free_copy_env(data_shell);
		clear_memory(*data_shell);
		exit(1);
	}
	else if (execve(data_shell->sentence_list->args[0],
			data_shell->sentence_list->args, data_shell->copy_env) == -1)
		message_error("Error with exec command", -1);
}

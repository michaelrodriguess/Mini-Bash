/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:42:30 by microdri          #+#    #+#             */
/*   Updated: 2023/04/11 17:16:09 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	open_pipes(t_data_shell *shell)
{
	int	pipefd[2];
	int	current_pipe;

	current_pipe = 0;
	shell->n_pipes = count_pipes(shell->tok_lst);
	shell->fd_pipes = malloc(sizeof(int) * 2 * shell->n_pipes);
	while (shell->n_pipes > current_pipe)
	{
		if (pipe(pipefd) == -1)
			message_error("Error with Pipe", -1);
		shell->fd_pipes[current_pipe * 2] = pipefd[0];
		shell->fd_pipes[(current_pipe * 2) + 1] = pipefd[1];
		current_pipe++;
	}
}

void	config_pipes(t_data_shell *shell)
{
	t_sentence	*head;
	int			cur_sent;

	head = shell->sentence_list;
	open_pipes(shell);
	cur_sent = 0;
	while (shell->n_pipes > cur_sent)
	{
		if (shell->sentence_list->prev != NULL
			&& shell->sentence_list->fd_in == 0)
			shell->sentence_list->fd_in = shell->fd_pipes[(cur_sent - 1) * 2];
		if (shell->sentence_list->fd_out == 1
			&& shell->sentence_list->next != NULL)
			shell->sentence_list->fd_out = shell->fd_pipes[(cur_sent * 2) + 1];
		shell->sentence_list = shell->sentence_list->next;
		cur_sent++;
	}
	if (shell->sentence_list->prev != NULL && shell->sentence_list->fd_in == 0)
		shell->sentence_list->fd_in = shell->fd_pipes[(cur_sent - 1) * 2];
	shell->sentence_list = head;
}

void	wait_sentences(t_data_shell *data_shell)
{
	t_sentence	*head;
	int			status;

	head = data_shell->sentence_list;
	g_var_global = 0;
	while (data_shell->sentence_list)
	{
		waitpid(data_shell->sentence_list->pid, &status, 0);
		if (WIFEXITED(status))
			g_var_global = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_var_global = 128 + WTERMSIG(status);
		if (data_shell->sentence_list->args == NULL)
			g_var_global = 127;
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

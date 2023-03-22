/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:42:30 by microdri          #+#    #+#             */
/*   Updated: 2023/03/22 14:02:33 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	config_pipes(t_data_shell *data_shell)
{
	int	pipefd[2];
	int	n_pipe;
	t_sentence *head;

	head = data_shell->sentence_list;
	n_pipe = count_pipes(data_shell->tok_lst);
	while (n_pipe > 0)
	{
		if(pipe(pipefd) == -1)
			message_error("Error with Pipe");
		data_shell->sentence_list->fd_in = pipefd[0];
		data_shell->sentence_list->fd_out = pipefd[1];
		data_shell->sentence_list = data_shell->sentence_list->next;
		n_pipe--;
	}
	data_shell->sentence_list->fd_in = pipefd[0];
	data_shell->sentence_list = head;
}

void	wait_sentences(t_data_shell *data_shell)
{
	t_sentence	*head;
	int			status;

	head = data_shell->sentence_list;
	while(data_shell->sentence_list)
	{
		waitpid(data_shell->sentence_list->pid, &status, 0);
		data_shell->sentence_list = data_shell->sentence_list->next;
	}
	data_shell->sentence_list = head;
}

void	close_pipes(t_data_shell *data_shell)
{
	t_sentence	*head;

	head = data_shell->sentence_list;
	while (head)
	{
		if (data_shell->sentence_list->prev != NULL)
			close(data_shell->sentence_list->fd_in);
		if (data_shell->sentence_list->next != NULL)
			close(data_shell->sentence_list->fd_in);
		data_shell->sentence_list = data_shell-> sentence_list->next;
	}
	data_shell->sentence_list = head;
	while (head)
	{
		if (data_shell->sentence_list->prev != NULL)
			close(data_shell->sentence_list->fd_in);
		if (data_shell->sentence_list->next != NULL)
			close(data_shell->sentence_list->fd_in);
		data_shell->sentence_list = data_shell-> sentence_list->prev;
	}
	data_shell->sentence_list = head;
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
			ft_putstr_fd("Error with Fork", 2);
		if (pid == 0)
		{
			if (n_sentence != 0)
			{
				dup2(data_shell->sentence_list->fd_in, 0);
				close(data_shell->sentence_list->fd_in);
			}
			if (n_sentence != (data_shell->number_of_sentence - 1))
			{
				dup2(data_shell->sentence_list->fd_out, 1);
				close(data_shell->sentence_list->fd_out);
			}
	//		close_pipes(data_shell);
			exec_pipes(data_shell);
		}
		data_shell->sentence_list->pid = pid;
		if (n_sentence != 0)
			close(data_shell->sentence_list->fd_in);
		if (n_sentence != (data_shell->number_of_sentence - 1))
			close(data_shell->sentence_list->fd_out);
		n_sentence++;
		data_shell->sentence_list = data_shell->sentence_list->next;
	}
	data_shell->sentence_list = head;
	wait_sentences(data_shell);
}

void	exec_pipes(t_data_shell *data_shell)
{
	if (execve(data_shell->sentence_list->args[0], data_shell->sentence_list->args, data_shell->copy_env) == -1)
		ft_putstr_fd("Error with command", 2);
}

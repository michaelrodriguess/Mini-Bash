/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:42:30 by microdri          #+#    #+#             */
/*   Updated: 2023/03/21 15:57:20 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// quantos pipes tem

void	config_pipes(t_data_shell *data_shell)
{
	int	pipefd[2];
	int	n_pipe;
	t_sentence *head;

	puts("config_pipes entrou");
	head = data_shell->sentence_list;
	n_pipe = count_pipes(data_shell->tok_lst);
	while (n_pipe > 0)
	{
		if(pipe(pipefd) == -1)
			message_error("Error with Pipe");
		data_shell->sentence_list->fd_in = pipefd[0];
		data_shell->sentence_list->fd_out = pipefd[1];
	
		printf("changed fd_in->%d fd_out->%d\n", data_shell->sentence_list->fd_in, data_shell->sentence_list->fd_out);
		data_shell->sentence_list = data_shell->sentence_list->next;
		n_pipe--;
	}
	data_shell->sentence_list = head;
}

void	config_forks(t_data_shell *data_shell)
{
	t_sentence	*head;
	int			pid;
	int			n_sentence;

	puts("config_forks entrou");
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
				dup2(data_shell->sentence_list->fd_in, 0);
			if (n_sentence != (data_shell->number_of_sentence - 1))
				dup2(data_shell->sentence_list->fd_out, 1);
	//		close(data_shell->sentence_list->fd_out);
	//		close(data_shell->sentence_list->fd_in);
			exec_pipes(data_shell);
		}
		close(data_shell->sentence_list->fd_out);
		close(data_shell->sentence_list->fd_in);
		n_sentence++;
		data_shell->sentence_list = data_shell->sentence_list->next;
	}
	usleep(2000000);
	data_shell->sentence_list = head;
}

// fds are not beeing configurated as expected, second sentence is not reading from prev sentence read fd;
//usleep must be replaced with waitpid loop 


void	exec_pipes(t_data_shell *data_shell)
{
	puts("exec_pipes entrou");
	if (execve(data_shell->sentence_list->args[0], data_shell->sentence_list->args, data_shell->copy_env) == -1)
		ft_putstr_fd("Error with command", 2);
}

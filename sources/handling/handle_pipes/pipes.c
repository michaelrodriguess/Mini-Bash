/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:42:30 by microdri          #+#    #+#             */
/*   Updated: 2023/03/20 18:46:52 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int		count_pipes(t_data_shell *data_shell)
{
	int		count;
	t_token	*temp;

	count = 0;
	temp = data_shell->tok_lst;
	while(temp != NULL)
	{
		if (temp->type == 1)
			count++;
		temp = temp->next;
	}
	data_shell->tok_lst = temp;
	return (count);
}

// quantos pipes tem
void	config_pipes(t_data_shell *data_shell)
{
	int	pipefd[2];
	int	n_pipe;
	t_sentence *head;

	head = data_shell->sentence_list;
	n_pipe = count_pipes(data_shell);
	while (n_pipe >= 0)
	{
		if(pipe(pipefd) == -1)
			message_error("Error with Pipe");
		data_shell->sentence_list->fd_in = pipefd[0];
		data_shell->sentence_list->fd_out = pipefd[1];
		data_shell->sentence_list = data_shell->sentence_list->next;
	
		printf("changed fd_in->%d fd_out->%d\n", data_shell->sentence_list->fd_in, data_shell->sentence_list_fd_out);
		n_pipe--;
	}
}


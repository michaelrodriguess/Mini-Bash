/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fcaetano@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:39:50 by fcaetano          #+#    #+#             */
/*   Updated: 2023/04/03 18:15:35 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	r_output(t_data_shell shell, int i_fd)
{
	int err;

	shell.tok_lst = shell.tok_lst->next;
	shell.fd_redis[i_fd] = open(shell.tok_lst->str, O_CREAT | O_RDWR | O_TRUNC, 0666);
	shell.sentence_list->fd_out = shell.fd_redis[i_fd];
	if (shell.sentence_list->fd_out == -1)
	{
		err = errno;
		message_error("Failed to open redirect output", err);//check returned value 
	}
}

/*
void	open_heredoc(t_data_shell *data_shell)
{
	char	*str;


}
*/


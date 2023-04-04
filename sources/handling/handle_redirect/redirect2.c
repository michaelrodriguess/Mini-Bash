/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fcaetano@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:39:50 by fcaetano          #+#    #+#             */
/*   Updated: 2023/04/04 17:13:29 by microdri         ###   ########.fr       */
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

char	*temp_file(int i_fd)
{
	char	*temp;
	char	*path_file;

	temp = ft_itoa(i_fd);
	path_file = ft_strjoin("../../../../../../../tmp/heredoc_temp", temp);
	free(temp);
	return (path_file);
}

void	open_heredoc(t_data_shell *data_shell, int i_fd)
{
	char	*str;
	char	*file_name;
	int		err;

	file_name = temp_file(i_fd);
	data_shell->fd_redis[i_fd] = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (data_shell->fd_redis[i_fd] == -1)
	{
		err = errno;
		message_error("Failed to open heredoc document", err);//check returned value 
	}
	while (42)
	{
		str = readline("heredoc> ");
		if (ft_strncmp(str, "", ft_strlen(str)) && !ft_strncmp(str, data_shell->tok_lst->next->str, ft_strlen(str)))
			break ;	
		ft_putstr_fd(str, data_shell->fd_redis[i_fd]);
		ft_putstr_fd("\n", data_shell->fd_redis[i_fd]);
	}
	close(data_shell->fd_redis[i_fd]);
	data_shell->fd_redis[i_fd] = open(file_name, O_RDONLY);
	data_shell->sentence_list->fd_in = data_shell->fd_redis[i_fd];
	free(file_name);
}

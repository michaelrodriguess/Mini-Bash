/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fcaetano@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:39:50 by fcaetano          #+#    #+#             */
/*   Updated: 2023/04/10 17:12:05 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	r_output(t_data_shell shell, int i_fd)
{
	if (shell.tok_lst->type == 2)
	{
		shell.fd_redis[i_fd] = open(shell.tok_lst->next->str,
				O_CREAT | O_RDWR | O_TRUNC, 0666);
		shell.sentence_list->fd_out = shell.fd_redis[i_fd];
	}
	else
	{
		shell.fd_redis[i_fd] = open(shell.tok_lst->next->str,
				O_CREAT | O_RDWR | O_APPEND, 0666);
		shell.sentence_list->fd_out = shell.fd_redis[i_fd];
	}
	if (shell.fd_redis[i_fd] == -1)
		message_error("Failed to open redirect output", 1);
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

void	open_heredoc(t_data_shell *shell, int i_fd)
{
	char	*str;
	char	*file_name;

	file_name = temp_file(i_fd);
	shell->fd_redis[i_fd] = open(file_name,
			O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (shell->fd_redis[i_fd] == -1)
		message_error("Failed to open heredoc document", 1);
	set_sig_heredoc();
	g_var_global = 0;
	while (42)
	{
		str = readline("heredoc> ");
		if ((!ft_strcmp(str, shell->tok_lst->next->str)
				|| str == NULL || g_var_global == 1))
			break ;
		ft_putstr_fd(str, shell->fd_redis[i_fd]);
		ft_putstr_fd("\n", shell->fd_redis[i_fd]);
	}
	set_sig();
	close(shell->fd_redis[i_fd]);
	shell->fd_redis[i_fd] = open(file_name, O_RDONLY);
	shell->sentence_list->fd_in = shell->fd_redis[i_fd];
	free(file_name);
}

void	r_input(t_data_shell shell, int i_fd)
{
	shell.fd_redis[i_fd] = open(shell.tok_lst->next->str, O_RDONLY);
	shell.sentence_list->fd_in = shell.fd_redis[i_fd];
	if (shell.fd_redis[i_fd] == -1)
		message_error("Failed to open redirect output", 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:42:30 by microdri          #+#    #+#             */
/*   Updated: 2023/03/18 23:40:23 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	pipes_cmd(t_data_shell *data_shell)
{
	int	pipe_fd[2];
	int	pid;
	
	if(pipe(pipe_fd) == -1)
		msg_error("Error with Pipe");
	pid = fork();
	if (pid == -1)
		msg_error("Error with fork");
	if (pid == 0)
	{
		close(pipe_fd[1]);
        dup2(pipefd[0], 0);
        close(pipefd[0]);  
        execve(pathname, data_shell->sentence_list->args, data_shell->copy_env); // executa o segundo comando
	}
	if (pid != 0)
	{
		close(pipefd[0]);
        dup2(pipefd[1], 1);
        close(pipefd[1]);
        execve(pathname, data_shell->sentence_list->args, data_shell->copy_env); // executa o primeiro comando
	}
}

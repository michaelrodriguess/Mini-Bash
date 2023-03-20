/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:42:30 by microdri          #+#    #+#             */
/*   Updated: 2023/03/20 15:02:59 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	pipes_cmd(t_data_shell *data_shell)
{
	int	pipefd[2];
	int	pid1;
	int	pid2;
	
	if(pipe(pipefd) == -1)
		message_error("Error with Pipe");
	pid1 = fork();
	if (pid1 == -1)
		message_error("Error with fork");
	if (pid1 == 0)
	{
		puts("1");
		close(pipefd[1]);
        dup2(pipefd[0], 0);
        close(pipefd[0]);  
        execve(data_shell->sentence_list->args[0], data_shell->sentence_list->args, data_shell->copy_env); // executa o segundo comando
	}
	pid2 = fork();
	if (pid2 == - 1)
		message_error("Error with fork");
	if (pid2 == 0)
	{
		puts("2");
		close(pipefd[0]);
        dup2(pipefd[1], 1);
        close(pipefd[1]);
        execve(data_shell->sentence_list->args[0], data_shell->sentence_list->args, data_shell->copy_env); // executa o primeiro comando
	}
}

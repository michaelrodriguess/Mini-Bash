/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:13:23 by microdri          #+#    #+#             */
/*   Updated: 2023/04/06 18:39:29 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_copy_env(char **env_copy)
{
	int	i;

	i = 0;
	while (env_copy[i])
	{
		free(env_copy[i]);
		i++;
	}
	free(env_copy);
}

void	clear_memory(t_data_shell data_shell, int end_exec)
{
	if (data_shell.input)
		free(data_shell.input);
	ft_tokclear(&data_shell.tok_lst);
	sentence_clear(&data_shell.sentence_list);
	if (data_shell.fd_pipes)
	{
		free(data_shell.fd_pipes);
		data_shell.fd_pipes = NULL;
	}
	if (data_shell.fd_redis)
	{
		free(data_shell.fd_redis);
		data_shell.fd_redis = NULL;
	}
	if (end_exec == 1)
	{
		clear_history();
		free_copy_env(data_shell.copy_env);
	}
}

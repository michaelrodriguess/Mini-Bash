/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:13:23 by microdri          #+#    #+#             */
/*   Updated: 2023/03/12 11:04:32 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_copy_env(t_data_shell *data_shell)
{
	int	i;

	i = 0;
	while (data_shell->copy_env[i])
	{
		free(data_shell->copy_env[i]);
		i++;
	}
	free(data_shell->copy_env);
}

void	clear_memory(char *input, t_data_shell data_shell)
{
	if (!input)
		return ;
	free(input);
	ft_tokclear(&data_shell.tok_lst);
}

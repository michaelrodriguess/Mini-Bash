/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:13:23 by microdri          #+#    #+#             */
/*   Updated: 2023/03/14 19:27:19 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
	if (input)
		free(input);
	ft_tokclear(&data_shell.tok_lst);
	free(data_shell.sentence_list->args);
	free(data_shell.sentence_list);
}

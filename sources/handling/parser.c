/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:45:22 by microdri          #+#    #+#             */
/*   Updated: 2023/03/14 07:47:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**parser(t_data_shell *data_shell)
{
	char	*command;

	if (data_shell->tok_lst == NULL)
		return (NULL);
	command = data_shell->tok_lst->str;
	if (is_builtin(command) == 1)
		parser_builtin(data_shell);
	else
	{
		data_shell->tok_lst->str = find_path(&command, data_shell->copy_env);
		free (command);
		printf("command: %s\n", data_shell->tok_lst->str);
	}
	return (NULL);
}

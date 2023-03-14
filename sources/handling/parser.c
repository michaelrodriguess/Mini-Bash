/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:45:22 by microdri          #+#    #+#             */
/*   Updated: 2023/03/14 10:27:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**parser(t_data_shell *data_shell) //sould be a void function
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
		if (data_shell->tok_lst->str)
			execute_cmd(data_shell);
		else 
			printf("Command %s not found.\n", command);
		free (command);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:45:22 by microdri          #+#    #+#             */
/*   Updated: 2023/03/14 11:54:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**parser(t_data_shell *data_shell) //sould be a void function?
{
	char	*command;

	if (data_shell->tok_lst == NULL)
		return (NULL);
	parser_builtin(data_shell); //transformar em função int para excluir proximo if
	if (!data_shell->sentence_list->args)
		return (NULL);
	command = data_shell->sentence_list->args[0];
	if (is_builtin(command) == 1)
	 	execute_builtins(data_shell);
	else
		execute_cmd(data_shell);
	free(data_shell->sentence_list->args);
	return (NULL);
}

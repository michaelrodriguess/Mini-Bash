/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:45:22 by microdri          #+#    #+#             */
/*   Updated: 2023/03/13 17:04:11 by microdri         ###   ########.fr       */
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
	{
		parser_builtin(data_shell);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:15:21 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/14 10:14:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_cmd(char *command, t_data_shell *data_shell)
{
	//parser_builtin(data_shell);
	(void) *data_shell;
	printf("Command: %s\n", command);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:52:54 by fcaetano          #+#    #+#             */
/*   Updated: 2023/04/10 11:58:12 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_flag(char *flag)
{
	int	i;

	i = 1;
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(char **args, int fd_out)
{
	int	n;
	int	i;

	if (args == NULL)
		return ;
	n = 1;
	i = 0;
	while (args[i] && !ft_strncmp(args[i], "-n", 2))
	{
		if (!check_flag(args[i]))
			break ;
		n = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], fd_out);
		if (args[i + 1] != NULL)
			ft_putstr_fd(" ", fd_out);
		i++;
	}
	if (n)
		ft_putstr_fd("\n", fd_out);
	g_var_global = 0;
}

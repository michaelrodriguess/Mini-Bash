/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:50:34 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/06 11:52:12 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(char **path)
{
	int	sz;

	sz = 0;
	if (path == NULL)
		return ;
		//get HOME from env
	while (path[sz])
		sz++;
	if (sz > 1)
		printf("too many arguments\n");
	else if (chdir(path[0]))
		ft_printf ("No such file or directory\n");
}

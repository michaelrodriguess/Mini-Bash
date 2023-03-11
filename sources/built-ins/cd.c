/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:41:35 by microdri          #+#    #+#             */
/*   Updated: 2023/03/11 18:42:15 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// get HOME from env

void	ft_cd(char **path)
{
	int	sz;

	sz = 0;
	if (path == NULL)
		return ;
	while (path[sz])
		sz++;
	if (sz > 1)
		printf("too many arguments\n");
	else if (chdir(path[0]))
		ft_printf ("No such file or directory\n");
}

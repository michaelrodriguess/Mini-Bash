/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:57:53 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/02 11:27:25 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, '\0');
	if (path)
		ft_printf("%s\n", path);
	else
		ft_printf("ERROR: getcwd returned a NULL pointer\n");
	free (path);
}

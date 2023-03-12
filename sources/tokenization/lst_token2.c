/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:10:14 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/11 19:38:09 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_toksize_w(t_token *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		if (lst->type == 0 || lst->type == 8)
			count++;
		lst = lst->next;
	}
	return (count);
}

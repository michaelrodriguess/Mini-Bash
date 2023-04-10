/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:10:14 by fcaetano          #+#    #+#             */
/*   Updated: 2023/04/10 09:21:50 by fcaetano         ###   ########.fr       */
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

void	remove_tok_nodes(t_token **lst, int n_nodes)
{
	t_token	*temp;

	while (n_nodes)
	{
		temp = (*lst)->next;
		free((*lst)->str);
		if ((*lst)->prev)
			(*lst)->prev->next = (*lst)->next;
		if ((*lst)->next)
			(*lst)->next->prev = (*lst)->prev;
		else
			temp = (*lst)->prev;
		free(*lst);
		*lst = NULL;
		*lst = temp;
		n_nodes--;
	}
}

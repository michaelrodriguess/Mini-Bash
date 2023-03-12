/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:17:38 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/12 11:12:55 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_toknew(int type, char *str)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = type;
	node->str = str;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_token	*ft_toklast(t_token *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_tokadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!(*lst))
		*lst = new;
	else
	{
		last = ft_toklast(*lst);
		if (last)
		{
			last->next = new;
			new->prev = last;
		}
	}
}

void	ft_tokclear(t_token **lst)
{
	t_token	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->str);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void	ft_tokprint(t_token *lst)
{
	while (lst)
	{
		ft_printf("type [%d] ", lst->type);
		ft_printf("str [%s]\n", lst->str);
		lst = lst->next;
	}
}

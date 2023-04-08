/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sentence_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:17:38 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/20 16:55:58 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_sentence	*sentence_new(char **args)
{
	t_sentence	*node;

	node = malloc(sizeof(t_sentence));
	if (!node)
		return (NULL);
	node->fd_in = 0;
	node->fd_out = 1;
	node->args = args;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_sentence	*sentence_last(t_sentence *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	sentence_add_back(t_sentence **lst, t_sentence *new)
{
	t_sentence	*last;

	if (!(*lst))
		*lst = new;
	else
	{
		last = sentence_last(*lst);
		if (last)
		{
			last->next = new;
			new->prev = last;
		}
	}
}

void	sentence_clear(t_sentence **lst)
{
	t_sentence	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->args);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

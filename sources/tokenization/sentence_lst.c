/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sentence_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:17:38 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/16 11:31:25 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_sentence	*sentence_new(int fd_in, int fd_out, char **args)
{
	t_sentence	*node;

	node = malloc(sizeof(t_sentence));
	if (!node)
		return (NULL);
	node->fd_in = fd_in;
	node->fd_out = fd_out;
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

void	sentence_print(t_sentence	*lst)
{
	int	i;

	while (lst)
	{
		printf("FD_IN [%d] ", lst->fd_in);
		printf("FD_OUT [%d] ", lst->fd_out);
		i = 0;
		while (lst->args && lst->args[i] != NULL)
			printf("args [%s]\n", lst->args[i++]);
		lst = lst->next;
	}
}

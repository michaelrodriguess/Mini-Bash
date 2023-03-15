/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:56:22 by microdri          #+#    #+#             */
/*   Updated: 2023/03/15 19:22:30 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	count_pipes(t_token *lst_tok)
{
	int count;
	if (!lst_tok)
		return (0);
	t_token *temp;

	temp = lst_tok;
	count = 0;
	while(temp != NULL)
	{
		if (temp->type == 1)
			count++;
		temp = temp->next;
	}
	return (count);
}

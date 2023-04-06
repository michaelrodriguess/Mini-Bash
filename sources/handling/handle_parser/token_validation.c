/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:33:57 by fcaetano          #+#    #+#             */
/*   Updated: 2023/04/06 17:15:37 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	val_pipe(t_token *token)
{
	if (token->prev == NULL || token->next == NULL)
		return (1);
	if (token->prev->type == 1 || token->next->type == 1)
		return (1);
	return (0);
}

int	val_redr(t_token *token)
{
	if (token->next == NULL || token->next->type == 1)
		return (1);
	return (0);
}

int	validation(t_token *token)
{
	while (token)
	{
		if (token->type == 1 && val_pipe(token))
			return (1);
		else if (token->type > 1 && token->type < 6 && val_redr(token))
			return (1);
		token = token->next;
	}
	return (0);
}

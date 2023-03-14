/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:33:57 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/14 14:32:36 by fcaetano         ###   ########.fr       */
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
	if (token->prev == NULL || token->next == NULL)
		return (1);
	return (0);
}

int	validation(t_token *token)
{
	int	quote;

	quote = 0;
	while (token)
	{
		if (token->type == 1 && val_pipe(token))
			return (1);
		else if (token->type < 6 && token->type > 1 && val_redr(token))
			return (1);
		else if ((token->type == 6 || token->type == 7) && !quote)
			quote = token->type;
		else if (quote && token->type == quote)
			quote = 0;
		token = token->next;
	}
	if (quote)
		return (1);
	return (0);
}

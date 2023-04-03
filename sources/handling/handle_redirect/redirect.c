/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fcaetano@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:11:29 by fcaetano          #+#    #+#             */
/*   Updated: 2023/04/03 14:05:04 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_token	*reset_head(t_token *tok_lst)
{
	while (tok_lst->prev && tok_lst->prev->type != 1)
		tok_lst = tok_lst->prev;
	return (tok_lst);
}

void	clean_input(t_data_shell *data_shell)
{
	while (data_shell->tok_lst && data_shell->tok_lst->next && data_shell->tok_lst->type != 1) //check unnecessary loop conditions
	{
		if (data_shell->tok_lst->type == 2)
			remove_tok_nodes(&(data_shell->tok_lst), 2);
		else
			data_shell->tok_lst = data_shell->tok_lst->next;
	}
	data_shell->tok_lst = reset_head(data_shell->tok_lst);
}

void	config_redirect(t_data_shell *data_shell)
{
	t_token	*head;

	head = data_shell->tok_lst;
	while (data_shell->tok_lst && data_shell->tok_lst->type != 1)
	{
		if (data_shell->tok_lst->type == 2 ||data_shell->tok_lst->type == 4)
			r_output(*data_shell);
		data_shell->tok_lst = data_shell->tok_lst->next;

	}
	data_shell->tok_lst = head;
}

void	redirect(t_data_shell *data_shell)
{
	config_redirect(data_shell);
	clean_input(data_shell);
}

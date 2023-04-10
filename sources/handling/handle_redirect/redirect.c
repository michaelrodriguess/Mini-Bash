/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fcaetano@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:11:29 by fcaetano          #+#    #+#             */
/*   Updated: 2023/04/10 13:59:30 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	count_redis(t_token *tok_lst)
{
	int	count;

	count = 0;
	while (tok_lst)
	{
		if (tok_lst->type > 1)
			count++;
		tok_lst = tok_lst->next;
	}
	return (count);
}

t_token	*reset_head(t_token *tok_lst)
{
	while (tok_lst && tok_lst->prev && tok_lst->prev->type != 1)
		tok_lst = tok_lst->prev;
	return (tok_lst);
}

void	clean_input(t_data_shell *data_shell)
{
	while (data_shell->tok_lst && data_shell->tok_lst->next
		&& data_shell->tok_lst->type != 1)
	{
		if (data_shell->tok_lst->type > 1)
			remove_tok_nodes(&(data_shell->tok_lst), 2);
		else
			data_shell->tok_lst = data_shell->tok_lst->next;
	}
	data_shell->tok_lst = reset_head(data_shell->tok_lst);
}

void	config_redirect(t_data_shell *shell)
{
	t_token			*head;

	head = shell->tok_lst;
	if (shell->n_redis == 0)
		shell->fd_redis = malloc(count_redis(shell->tok_lst) * sizeof(int));
	if (!shell->fd_redis)
		message_error("Error with malloc fd_redis", -1);
	while (shell->tok_lst && shell->tok_lst->type != 1)
	{
		if (shell->tok_lst->type == 2 || shell->tok_lst->type == 4)
			r_output(*shell, shell->n_redis);
		else if (shell->tok_lst->type == 5)
			open_heredoc(shell, shell->n_redis);
		else if (shell->tok_lst->type == 3)
			r_input(*shell, shell->n_redis);
		if (shell->tok_lst->type > 1)
			shell->n_redis++;
		shell->tok_lst = shell->tok_lst->next;
	}
	if (shell->tok_lst == NULL)
		shell->n_redis = 0;
	shell->tok_lst = head;
}

void	redirect(t_data_shell *data_shell)
{
	config_redirect(data_shell);
	clean_input(data_shell);
}

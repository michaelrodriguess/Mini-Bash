/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:20:56 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/02 10:28:27 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*cat_envvar(char **qt_str)
{
	t_token	*current;
	int		sz;

	sz = 0;
	while (ft_isalnum((*qt_str)[sz]))
		sz++;
	current = ft_toknew(0, ft_substr(*qt_str, 0, sz));
	(*qt_str) += sz;
	return (current);
}

t_token	*cat_dollar(char *qt_str)
{
	t_token	*head;
	int		sz;

	sz = 0;
	head = NULL;
	ft_printf("%s\n", qt_str);
	while (qt_str[sz])
	{
		if (qt_str[sz] == '$')
		{
			ft_tokadd_back(&head, special_chr(8, &qt_str));
			ft_tokadd_back(&head, cat_envvar(&qt_str));
		}
		else
			ft_tokadd_back(&head, cat_word(&qt_str, "$"));
	}
	return (head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:20:56 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/06 18:57:21 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*t_token	*cat_envvar(char **qt_str)
{
	t_token	*current;
	int		sz;

	sz = 1;
	while (!ft_strchri(" |<>$", (*qt_str)[sz]))
		sz++;
	current = ft_toknew(8, ft_substr(*qt_str, 0, sz));
	(*qt_str) += sz;
	return (current);
}

t_token	*cat_dollar(char *qt_str)
{
	t_token	*head;
	int		sz;

	sz = 0;
	head = NULL;
	while (qt_str[sz])
	{
		if (qt_str[sz] == '$')
			ft_tokadd_back(&head, cat_envvar(&qt_str));
		else
			ft_tokadd_back(&head, cat_word(&qt_str, "$"));
	}
	return (head);
}*/

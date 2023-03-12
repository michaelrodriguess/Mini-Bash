/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:11:58 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/09 11:26:03 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*cat_word(char **c_line, char *chr_set)
{
	t_token	*current;
	int		sz;
	char	quote;

	sz = 0;
	while (!ft_strchri(chr_set, (*c_line)[sz]) && (*c_line)[sz])
	{
		if (ft_strchri("\'\"", (*c_line)[sz]))
		{
			quote = (*c_line)[sz];
			sz++;
			while ((*c_line)[sz] != quote && (*c_line)[sz])
				sz++;
		}
		if ((*c_line)[sz])
			sz++;
	}
	current = ft_toknew(0, ft_substr(*c_line, 0, sz));
	(*c_line) += sz;
	return (current);
}

t_token	*special_chr(int type, char **c_line)
{
	t_token	*current;
	char	*str;

	str = ft_substr(*c_line, 0, 1);
	if (type == 2 || type == 3)
	{
		if (ft_strchri("|><><\"\'$-", (*c_line)[1]) == type)
		{
			type += 2;
			free(str);
			str = ft_substr(*c_line, 0, 2);
			(*c_line)++;
		}
	}
	current = ft_toknew(type, str);
	(*c_line)++;
	return (current);
}

t_token	*cat_quoteword(char **c_line, int type)
{
	t_token	*current;
	char	*str;
	int		sz;

	sz = 0;
	while (((type == 6 && (*c_line)[sz] != '"')
		|| (type == 7 && (*c_line)[sz] != '\'')) && (*c_line)[sz])
		sz++;
	str = ft_substr(*c_line, 0, sz);
	current = ft_toknew(0, str);
	(*c_line) += sz;
	return (current);
}

t_token	*lexer(char *c_line)
{
	t_token	*head;
	int		type;

	head = NULL;
	type = 0;
	while (*c_line)
	{
		type = ft_strchri("|><><", *c_line);
		if (type)
			ft_tokadd_back(&head, special_chr(type, &c_line));
		else if ((*c_line) != ' ')
			ft_tokadd_back(&head, cat_word(&c_line, " |><><"));
		else
			c_line++;
	}
	return (head);
}

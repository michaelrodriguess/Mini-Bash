/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:11:58 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/08 14:58:18 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*cat_word(char **c_line, char *chr_set)
{
	t_token	*current;
	int		sz;

	sz = 0;
	while (!ft_strchri(chr_set, (*c_line)[sz]))
		sz++;
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
	t_token	*tmp;
	char	*str;
	int		sz;

	sz = 0;
	while (((type == 6 && (*c_line)[sz] != '"')
		|| (type == 7 && (*c_line)[sz] != '\'')) && (*c_line)[sz])
		sz++;
	str = ft_substr(*c_line, 0, sz);
	current = ft_toknew(0, str);
	if (ft_strchr(str, '$') && type == 6)
	{
		tmp = current;
		current = cat_dollar(str);
		ft_tokclear(&tmp);
	}
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
		type = ft_strchri("|><><\"\'$", *c_line);
		if (type && type != 8)
			ft_tokadd_back(&head, special_chr(type, &c_line));
		else if (type == 8)
			ft_tokadd_back(&head, cat_envvar(&c_line));
		else if ((*c_line) != ' ')
			ft_tokadd_back(&head, cat_word(&c_line, " |><><"));
		else
			c_line++;
		if (type == 6 || type == 7)
		{
			ft_tokadd_back(&head, cat_quoteword(&c_line, type));
			if (type == ft_strchri("|><><\"\'$-", (*c_line)))
				ft_tokadd_back(&head, special_chr(type, &c_line));
		}
	}
	return (head);
}

/*int main(void)
{
	char	*command = "echo test \"|$PWD.test' \"'' ";
	t_token	*token;

	command = ft_strdup(command);
	token = lexer(command);
	if (token)
	{
		ft_tokprint(token);
		if (validation(token))
			ft_printf("\nError.\n");
		else
			ft_printf("\n%s\n", command);
		ft_tokclear(&token);
	}
	free(command);
}*/

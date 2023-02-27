//HEADER

#include "../includes/minishell.h"

t_token	*cat_word(char **c_line, char *chr_set)
{
	t_token	*current;
	int		sz;

	sz = 0;
	current = malloc(sizeof(t_token));
	while (!ft_strchri(chr_set, (*c_line)[sz]))
		sz++;
	current->type = 0;
	current->str = ft_substr(*c_line, 0, sz);
	current->next = NULL;
	(*c_line)+= sz;
	return(current);
}

t_token	*special_chr(int type, char **c_line)
{
	t_token	*current;
	char	*str;

	current = malloc(sizeof(t_token));
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
	current->type = type;
	current->str = str;
	current->next = NULL;
	(*c_line)++;
	return(current);
}

t_token	*cat_envvar(char **qt_str)
{
	t_token	*current;
	int		sz;

	sz = 0;
	current = malloc(sizeof(t_token));
	while (ft_isalnum((*qt_str)[sz]))
		sz++;
	current->type = 0;
	current->str = ft_substr(*qt_str, 0, sz);
	current->next = NULL;
	(*qt_str)+= sz;
	return(current);
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

t_token	*cat_quoteword(char **c_line, int type)
{
	t_token	*current;
	t_token	*tmp;
	char	*str;
	int		sz;

	sz = 0;
	current = malloc(sizeof(t_token));
	while ((type == 6 && (*c_line)[sz] != '"') || (type == 7 && (*c_line)[sz] != '\''))
		sz++;
	str = ft_substr(*c_line, 0, sz);
	current->type = 0;
	current->str = str;
	current->next = NULL;
	if (ft_strchr(str, '$') && type == 6)
	{
		tmp = current;
		current = cat_dollar(str);
		ft_tokclear(&tmp);
	}
	(*c_line)+= sz;
	return(current);
}


t_token	*lexer(char* c_line)
{
	t_token *head;
	int		type;

	head = NULL;
	type = 0;
	while (*c_line)
	{
		type = ft_strchri("|><><\"\'$-", *c_line);
		if (type)
			ft_tokadd_back(&head, special_chr(type, &c_line));
		else if ((*c_line) != ' ')
			ft_tokadd_back(&head, cat_word(&c_line, " |><><"));
		else
			c_line++;
		if (type == 6 || type == 7)
		{
			ft_tokadd_back(&head, cat_quoteword(&c_line, type));
			if (type == ft_strchri("|><><\"\'$-", *c_line))
				ft_tokadd_back(&head, special_chr(type, &c_line));
		}
		else if (type == 8)
			ft_tokadd_back(&head, cat_envvar(&c_line));
	}
	return (head);
}

int main (void)
{
	char	*command = " test $PWD.test   ";
	t_token	*token;

	command = ft_strdup(command);
	ft_printf("%s\n", command);
	token = lexer(command);
	if (token)
	{
		ft_tokprint(token);
		ft_tokclear(&token);
	}
	free(command);
}

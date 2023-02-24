//HEADER

#include "../includes/minishell.h"

t_token	*cat_word(char **c_line)
{
	t_token	*current;
	int		sz;

	sz = 0;
	current = malloc(sizeof(t_token));
	while (!ft_strchri(" |><><", (*c_line)[sz]) && (*c_line)[sz] != ' ')
		sz++;
	current->type = 0;
	current->str = ft_substr(*c_line, 0, sz);
	current->next = NULL;
	(*c_line)+= sz;
	return(current);
}

t_token	*cat_envvar(char *qt_str) //não usar a split, ir percorrendo a string ??
{
	t_token *head;
	t_token *current;
	int		sz;

	sz = -1;
	head = NULL;
	while (qt_str[sz++])
	{
		if (qt_str[sz] == '$' || !(qt_str[sz + 1]))
		{
			if (sz > 0)
			{
				current = malloc(sizeof(t_token));
				current->type = 0;
				current->str = ft_substr(qt_str, 0, sz);
				ft_tokadd_back(&head, current);
			}
			if (qt_str[sz] != '$')
				return (head);
			current = malloc(sizeof(t_token));
			current->type = 8;
			current->str = "$";
			ft_tokadd_back(&head, current);
			qt_str += sz + 1;
			sz = -1;
		}
	}
	return (head);
}

/* 	t_token	*head;
	t_token *current;
	char	**str_split;
	int		envvar;

	envvar = 0;
	str_split = ft_split(qt_str, '$');
	head = malloc(sizeof)
	if (*qt_str == '&')
	{
		head->type = 8;
		head->str = "&";
	}
	else
	{
		head->type = 0;
		head->str = str_split[0];
		envvar++;
	}
	while (str_split[envvar])
	{

	}
	ft_printf("%s\n%s\n", str_split[0], str_split[1]); */

t_token	*cat_quoteword(char **c_line, int type)
{
	t_token	*current;
	char	*str;
	int		sz;

	sz = 0;
	current = malloc(sizeof(t_token));
	while ((type == 6 && (*c_line)[sz] != '"') || (type == 7 && (*c_line)[sz] != '\''))
	{
		sz++;
	}
	str = ft_substr(*c_line, 0, sz);
	current->type = 0;
	current->str = str;
	current->next = NULL;
	if (ft_strchr(str, '$') && type == 6)
		current = cat_envvar(*c_line);
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
		if (ft_strchri(" |><><\"\'$-", (*c_line)[1]) == type)
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

t_token	*lexer(char* c_line)
{
	t_token *head;
	int		type;

	head = NULL;
	type = 0;
	while (*c_line)
	{
		if (type == 6 || type == 7)
			ft_tokadd_back(&head, cat_quoteword(&c_line, type));
		type = ft_strchri(" |><><\"\'$-", *c_line);
		if (type)
			ft_tokadd_back(&head, special_chr(type, &c_line));
		else if ((*c_line) != ' ')
			ft_tokadd_back(&head, cat_word(&c_line));
		else
			c_line++;
	}
	return (head);
}

int main (void)
{
	char	*command;
	t_token	*token;

	command = ft_strdup("ls -la >> grep \"test e \'agora\' $ENVVAR \"");
	ft_printf("%s\n", command);
	token = lexer(command);
	if (token)
	{
		ft_tokprint(token);
		ft_tokclear(&token);
	}
	free(command);
}

//resstrutrar -> mudar função de cat word para receber os parâmetros de parada usando a ft_strchri, talvez seja necessário alterar a ft_strchri
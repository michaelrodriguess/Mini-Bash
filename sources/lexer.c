//HEADER

#include "../includes/minishell.h"

t_token	*cat_word(char **c_line)
{
	t_token	*current;
	// char	*str;
	int		sz;

	sz = 0;
	current = malloc(sizeof(t_token));
	while (!ft_strchri(" |><><\"\'$-", (*c_line)[sz]) && (*c_line)[sz] != ' ')
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
	return(current);
}

t_token	*lexer(char* c_line)
{
	// t_token *head;
	t_token	*current;
	int		type;

	current = NULL;
	type = ft_strchri(" |><><\"\'$-", *c_line);
	if (type)
		current = special_chr(type, &c_line);
	else if ((*c_line) != ' ')
		current = cat_word(&c_line);
	if (current)
	{
		ft_printf("%i\n", current->type);
		ft_printf("%s$\n", current->str);
	}
	ft_printf("%s\n", c_line);
	return (current);
}

int main (void)
{
	char	*command;
	t_token	*token;

	command = ft_strdup("ls -la | grep test");
	ft_printf("%s\n", command);
	token = lexer(command);
	if (token)
	{
		free(token->str);
		free(token);
	}
	free(command);
}
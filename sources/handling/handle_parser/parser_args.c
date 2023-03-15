/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:20:34 by microdri          #+#    #+#             */
/*   Updated: 2023/03/15 20:20:12 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*quote(char	**arg, char *parsed_arg, char **env)
{
	int		i;
	char	*ret;
	char	*temp;
	char	quote;

	i = 0;
	quote = **arg;
	while ((*arg)[i + 1] != quote && (*arg)[i + 1])
		i++;
	temp = ft_substr((*arg), 1, i);
	if (quote == '\"' && ft_strchri(temp, '$'))
		expand_str(&temp, env);
	ret = ft_strjoin(parsed_arg, temp);
	free(temp);
	if ((*arg)[i + 1])
		i++;
	(*arg) += i + 1;
	return (ret);
}

char	*parse_arg(char *arg, char **env)
{
	char	*parsed_arg;
	char	*temp;

	parsed_arg = ft_strdup("");
	while (*arg)
	{
		if (!parsed_arg)
			parsed_arg = ft_strdup("");
		temp = parsed_arg;
		if (*arg == '\"' || *arg == '\'')
			parsed_arg = quote(&arg, parsed_arg, env);
		else if (*arg == '$' && (arg[1] == '_' || ft_isalnum(arg[1])))
			parsed_arg = cat_envvar(&arg, parsed_arg, env);
		else
		{
			parsed_arg = strjoinchr(parsed_arg, *arg);
			arg++;
		}
		free(temp);
	}
	return (parsed_arg);
}

static char	*add_arg(t_data_shell *data_shell)
{
	char	*arg;
	char	*temp;

	arg = NULL;
	if (data_shell->tok_lst)
	{
		arg = data_shell->tok_lst->str;
		if (ft_strchri(arg, '$') || ft_strchri(arg, '\'')
			|| ft_strchri(arg, '\"'))
		{
			temp = arg;
			arg = parse_arg(arg, data_shell->copy_env);
			free(temp);
			data_shell->tok_lst->str = arg;
		}
		data_shell->tok_lst = data_shell->tok_lst->next;
	}
	return (arg);
}

void	tok_list_to_args(t_data_shell *data_shell)
{
	int		size;
	int		index;

	index = 0;
	data_shell->sentence_list->args = NULL;
	if (data_shell->tok_lst != NULL)
	{
		if (!is_builtin(data_shell->tok_lst->str))	// colocar find_cmd para retornar int e mudar para um só if
			find_cmd(data_shell);					// if(!is_builtin(data_shell->tok_lst->str && !find_cmd(data_shell))
		if (!data_shell->tok_lst->str)
			return ;
		size = ft_toksize_w(data_shell->tok_lst);
		data_shell->sentence_list->args = malloc((size + 1) * sizeof(char *));
		if (!data_shell->sentence_list->args)
			printf("Error in parser built-in malloc.\n");
		while (data_shell->tok_lst != NULL && data_shell->tok_lst->type != 1)
		{
			if (data_shell->tok_lst->type == 0)
				data_shell->sentence_list->args[index] = add_arg(data_shell);
			if (data_shell->sentence_list->args[index])
				index++;
		}
		data_shell->sentence_list->args[index] = NULL;
	}
}

void	parser(t_data_shell *data_shell)
{
	t_sentence *head;

	if (data_shell->tok_lst == NULL)
	{
		data_shell->sentence_list->args = NULL;
		return ;
	}
	data_shell->sentence_list = sentence_new(-1, -1, NULL);
	head = data_shell->sentence_list;
	while (data_shell->tok_lst != NULL)
	{
		tok_list_to_args(data_shell);
		if (data_shell->tok_lst != NULL)
		{
			sentence_add_back(&data_shell->sentence_list, sentence_new(-1, -1, NULL));
			data_shell->tok_lst = data_shell->tok_lst->next;
			data_shell->sentence_list = data_shell->sentence_list->next;
		}
	}
	data_shell->sentence_list = head;
}

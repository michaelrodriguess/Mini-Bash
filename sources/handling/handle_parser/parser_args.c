/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:20:34 by microdri          #+#    #+#             */
/*   Updated: 2023/04/08 16:39:10 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
		else if (*arg == '$' && arg[1] == '?')
			parsed_arg = cat_exitstatus(&arg, parsed_arg);
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
	if (!data_shell->tok_lst)
		return ;
	if (!is_builtin(data_shell->tok_lst->str) && !find_cmd(data_shell))
	{
		while (data_shell->tok_lst && data_shell->tok_lst->type != 1)
			data_shell->tok_lst = data_shell->tok_lst->next;
		return ;
	}
	size = ft_toksize_w(data_shell->tok_lst);
	data_shell->sentence_list->args = malloc((size + 1) * sizeof(char *));
	if (!data_shell->sentence_list->args)
		ft_putstr_fd("Error malloc.\n", 2);
	while (data_shell->tok_lst != NULL && data_shell->tok_lst->type != 1)
	{
		if (data_shell->tok_lst->type == 0)
			data_shell->sentence_list->args[index] = add_arg(data_shell);
		if (data_shell->sentence_list->args[index])
			index++;
	}
	data_shell->sentence_list->args[index] = NULL;
}

int	has_redirect(t_token *tok_lst)
{
	while (tok_lst && tok_lst->type != 1)
	{
		if (tok_lst->type > 1)
			return (1);
		tok_lst = tok_lst->next;
	}
	return (0);
}

void	parser(t_data_shell *data_shell)
{
	t_sentence	*head_sent;
	t_token		*head_tok;

	if (data_shell->tok_lst == NULL)
		return ;
	data_shell->sentence_list = sentence_new(NULL);
	head_sent = data_shell->sentence_list;
	while (data_shell->tok_lst != NULL)
	{
		if (has_redirect(data_shell->tok_lst))
			redirect(data_shell);
		if (data_shell->sentence_list->prev == NULL)
			head_tok = data_shell->tok_lst;
		tok_list_to_args(data_shell);
		if (data_shell->tok_lst != NULL)
		{
			sentence_add_back(&data_shell->sentence_list, sentence_new(NULL));
			data_shell->tok_lst = data_shell->tok_lst->next;
			data_shell->sentence_list = data_shell->sentence_list->next;
		}
	}
	data_shell->sentence_list = head_sent;
	data_shell->tok_lst = head_tok;
}

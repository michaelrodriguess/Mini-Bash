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

void	expand_exit_status(char **str)
{
	char	*current_exit_status;
	int		i;

	current_exit_status = ft_itoa(g_var_global);
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && ((*str)[i + 1] == '?'))
		{
			insert_envvar(str, current_exit_status, i, i + 2);
			i++;
		}
		else
			i++;
	}
	free(current_exit_status);
}

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
	if (quote == '\"' && ft_strchri(ret, '$'))
		expand_exit_status(&ret);
	return (ret);
}

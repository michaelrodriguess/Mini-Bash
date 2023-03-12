/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:47:39 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/09 17:12:51 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_substr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fcaetano@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:44:27 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/11 16:44:29 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*remove_substr(char	*str, int from, int to)
{
	char	*ret;
	char	*temp;
	char	*suffix;

	ret = ft_substr(str, 0, from);
	suffix = ft_substr(str, to + 1, ft_strlen(&str[to]));
	temp = ret;
	ret = ft_strjoin(ret, suffix);
	free(temp);
	free(suffix);
	return (ret);
}

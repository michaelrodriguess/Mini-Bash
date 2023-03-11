/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_substr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fcaetano@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:44:11 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/11 16:44:14 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*insert_substr(char	*str, char *substr, int i)
{
	char	*ret;
	char	*temp;
	char	*suffix;

	ret = ft_substr(str, 0, i);
	suffix = ret;
	ret = ft_strjoin(ret, substr);
	free(suffix);
	suffix = ft_substr(str, i, ft_strlen(&str[i]));
	temp = ret;
	ret = ft_strjoin(ret, suffix);
	free(temp);
	free(suffix);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:03:23 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/02 17:38:40 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*ret;
	int		c;

	c = ft_strlen(src) + 1;
	ret = malloc(c * sizeof(*ret));
	if (!ret)
		return (ret);
	c = 0;
	while (src[c])
	{
		ret[c] = src[c];
		c++;
	}
	ret[c] = 0;
	return (ret);
}

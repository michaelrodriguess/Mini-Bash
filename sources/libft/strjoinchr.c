/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoinchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:50:33 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/09 14:54:22 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strjoinchr(char *str, char chr)
{
	char	*ret;
	int		i;

	if (!str)
		return (NULL);
	ret = malloc(sizeof(char) * ft_strlen(str) + 2);
	i = 0;
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = chr;
	ret[i + 1] = 0;
	return (ret);
}

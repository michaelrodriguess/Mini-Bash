/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:02:48 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/02 17:37:16 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*tdest;
	char	*tsrc;

	if (!dest && !src)
		return (NULL);
	tdest = dest;
	tsrc = (char *)src;
	if (tdest < tsrc)
	{
		while (len--)
			*tdest++ = *tsrc++;
	}
	else
	{
		tsrc += len - 1;
		tdest += len - 1;
		while (len--)
			*tdest-- = *tsrc--;
	}
	return (dest);
}

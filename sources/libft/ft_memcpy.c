/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:55:00 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/02 17:37:04 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*ptrdest;
	const char	*ptrsrc;

	if (!dest && !src)
		return (NULL);
	ptrdest = dest;
	ptrsrc = src;
	while (n > 0)
	{
		ptrdest[n - 1] = ptrsrc[n - 1];
		n--;
	}
	return (dest);
}

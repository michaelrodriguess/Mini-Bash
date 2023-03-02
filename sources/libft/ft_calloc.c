/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:00:49 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/02 17:34:58 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	int		i;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	i = count * size - 1;
	while (i >= 0)
		((char *)ptr)[i--] = 0;
	return (ptr);
}

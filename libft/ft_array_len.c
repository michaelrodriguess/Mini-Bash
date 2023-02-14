/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:20:13 by fcaetano          #+#    #+#             */
/*   Updated: 2023/01/16 11:20:15 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_array_len(char **str)
{
	size_t	n;

	if (!str)
		return (0);
	n = 0;
	while (str[n])
		n++;
	return (n);
}
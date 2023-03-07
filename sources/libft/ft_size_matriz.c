/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_matriz.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:18:50 by microdri          #+#    #+#             */
/*   Updated: 2023/03/07 17:27:24 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_size_matriz(char **matriz)
{
	int	count;

	count = 0;
	while(matriz[count] != NULL)
		count++;
	return (count);
}

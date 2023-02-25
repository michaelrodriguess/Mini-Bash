/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:55:20 by fcaetano          #+#    #+#             */
/*   Updated: 2023/02/25 08:45:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchri(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((char)c == s[i])
			return (i + 1);
		i++;
	}
	if ((char)c == s[i])
		return (i + 1);
	return (0);
}

/* #include <stdio.h>
int main(void)
{
    char s[] = "|><><\"\'$- ";
    int c;
    int	ret;

    c = '|';
    printf("%s\n", s);
    ret = ft_strchri(s, c);
    printf("%d\n", ret);
    return (0);
} */
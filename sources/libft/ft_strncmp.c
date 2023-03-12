/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:53:00 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/09 11:06:41 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;
	unsigned char	c1;
	unsigned char	c2;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]) && i < n)
	{
		i++;
	}
	if (i == n)
	{
		c1 = s1[i - 1];
		c2 = s2[i - 1];
		return (c1 - c2);
	}
	c1 = s1[i];
	c2 = s2[i];
	return (c1 - c2);
}

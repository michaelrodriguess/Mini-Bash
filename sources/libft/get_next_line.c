/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:41:50 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/02 17:41:04 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read(int fd)
{
	int		bread;
	char	*readbuf;

	readbuf = malloc(BUFFER_SIZE + 1 * sizeof(*readbuf));
	if (!readbuf)
		return (readbuf);
	bread = read(fd, readbuf, BUFFER_SIZE);
	if (bread == 0)
	{
		free(readbuf);
		return (ft_strdup(""));
	}
	readbuf[bread] = 0;
	if (bread < 0)
	{
		free(readbuf);
		return (0);
	}
	else
		return (readbuf);
}

char	*check_bread(char *sbuf, char *line, int nli)
{
	char	*temp;

	if (!sbuf)
		return (0);
	nli = ft_i_strchr(sbuf, '\n');
	ft_strlcpy(line, sbuf, nli + 2);
	temp = sbuf;
	sbuf = ft_strdup(sbuf + nli + 1);
	if (temp)
		free(temp);
	return (sbuf);
}

char	*check_eof(char *sbuf, char *temp)
{
	if (temp == 0)
	{
		if (sbuf)
			free(sbuf);
		return (0);
	}
	if (ft_strlen(sbuf) > 0)
	{
		free(temp);
		return (sbuf);
	}
	free(temp);
	free(sbuf);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*sbuf;
	char		*line;
	int			nli;

	if (fd < 0)
		return (0);
	while (1)
	{
		nli = ft_i_strchr(sbuf, '\n');
		if (nli >= 0)
		{
			line = malloc((nli + 2) * sizeof(*line));
			sbuf = check_bread(sbuf, line, nli);
			return (line);
		}
		line = ft_read(fd);
		if (ft_strlen(line) == 0)
		{
			line = check_eof(sbuf, line);
			sbuf = 0;
			return (line);
		}
		sbuf = ft_strjoin_gnl(sbuf, line);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 07:26:46 by fcaetano          #+#    #+#             */
/*   Updated: 2023/04/08 16:37:23 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*search_matrix(char **matrix, char **cmd)
{
	char	*path_temp;
	char	*pathname;
	int		i;

	i = 0;
	while (matrix[i])
	{
		pathname = ft_strjoin(matrix[i], "/");
		path_temp = ft_strjoin(pathname, cmd[0]);
		free(pathname);
		if (try_path(path_temp) == 1)
		{
			clear_matrix(matrix);
			return (path_temp);
		}
		free(path_temp);
		path_temp = NULL;
		i++;
	}
	clear_matrix(matrix);
	return (path_temp);
}

char	*try_matrix_path(char **envp, char **cmd)
{
	char	**matrix;
	char	*pathname;

	pathname = NULL;
	matrix = matrix_path(envp);
	if (matrix == NULL)
		return (NULL);
	pathname = search_matrix(matrix, cmd);
	return (pathname);
}

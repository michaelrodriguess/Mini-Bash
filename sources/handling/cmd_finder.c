/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 07:26:46 by fcaetano          #+#    #+#             */
/*   Updated: 2023/03/14 07:59:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**matrix_path(char **envp)
{
	int		index;
	char	**matrix;

	index = 0;
	matrix = NULL;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
		{	
			matrix = ft_split(&envp[index][5], ':');
			break ;
		}
		index++;
	}
	return (matrix);
}

static void	clear_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

char	*find_path(char **cmd, char **envp)
{
	int		i;
	char	*pathname;
	char	*path_temp;
	char	**matrix;

	i = 0;
	pathname = NULL;
	matrix = matrix_path(envp);
	while (matrix[i])
	{
		pathname = ft_strjoin(matrix[i], "/");
		path_temp = ft_strjoin(pathname, cmd[0]);
		free(pathname);
		if (access(path_temp, F_OK | X_OK) == 0)
		{
			clear_matrix(matrix);
			return (path_temp);
		}
		free(path_temp);
		i++;
	}
	clear_matrix(matrix);
	return (path_temp);
}
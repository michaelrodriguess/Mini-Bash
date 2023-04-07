/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 07:26:46 by fcaetano          #+#    #+#             */
/*   Updated: 2023/04/07 14:30:43 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

int		try_path(char *str)
{

	if (str[0] == '/' || str[0] == '.')
	{
		if (access(str, F_OK | X_OK) == 0)
			return (1);
	}
	return (0);
}

char	*try_matrix_path(char **envp, char **cmd)
{
	char	**matrix;
	char	*path_temp;
	char	*pathname;
	int		i;

	i = 0;
	pathname = NULL;
	matrix = matrix_path(envp);
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

char	*find_path(char **cmd, char **envp)
{
	char	*path_try;
	char	*path_temp;

	path_try = ft_strdup(cmd[0]);
	if (try_path(path_try) == 1)
		return (path_try);
	free(path_try);
	path_temp = try_matrix_path(envp, cmd);
	return (path_temp);
}

int	find_cmd(t_data_shell *data_shell)
{
	char	*temp;

	temp = data_shell->tok_lst->str;
	data_shell->tok_lst->str = find_path(&(data_shell->tok_lst->str), data_shell->copy_env);
	free(temp);
	if (data_shell->tok_lst->str)
		return (1);
	else
		return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:50:34 by fcaetano          #+#    #+#             */
/*   Updated: 2023/04/07 16:43:57 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_envvar(char **env, char *var)
{
	while (*env && ft_strncmp(*env, var, ft_strchri(*env, '=') - 1))
		env++;
	if (!*env)
		return (NULL);
	return (&((*env)[ft_strchri(*env, '=')]));
}

void	updat_env(char ***env)
{
	char	**new_var;
	char	*temp;

	new_var = malloc(sizeof(char *) * 2);
	new_var[1] = NULL;
	new_var[0] = get_envvar(*env, "PWD");
	new_var[0] = ft_strjoin("OLDPWD=", new_var[0]);
	ft_export(new_var, env);
	free(new_var[0]);
	new_var[0] = getcwd(NULL, '\0');
	temp = new_var[0];
	new_var[0] = ft_strjoin("PWD=", new_var[0]);
	free(temp);
	ft_export(new_var, env);
	free(new_var[0]);
	free(new_var);
}

void	ft_cd(char **args, char ***env)
{
	char	*path;

	if (*args == NULL)
	{
		path = get_envvar(*env, "HOME");
		if (!path)
		{
			message_error("cd: HOME not set", 1);
			return ;
		}
	}
	else
		path = *args;
	if (chdir(path))
		message_error("microtano: cd: No such file, directory or permissions",
			1);
	else
		updat_env(env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:57:53 by fcaetano          #+#    #+#             */
/*   Updated: 2023/04/07 17:19:25 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(char **env_copy)
{
	char	*path;
	char	*pwd_env;

	pwd_env = get_envvar(env_copy, "PWD");
	path = getcwd(NULL, '\0');
	if (path)
		ft_printf("%s\n", path);
	else if (pwd_env)
		ft_printf("%s\n", pwd_env);
	else
		ft_printf("ERROR: getpwd returned a NULL pointer\n");
	free (path);
}

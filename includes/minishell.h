/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:50:06 by microdri          #+#    #+#             */
/*   Updated: 2023/02/23 18:46:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*next;
} t_token;

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include "../sources/libft/libft.h"

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:50:06 by microdri          #+#    #+#             */
/*   Updated: 2023/02/28 14:32:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*next;
	struct s_token	*prev;
} t_token;

t_token	*ft_toknew(int type, char *str);
t_token	*ft_toklast(t_token *lst);
void	ft_tokadd_back(t_token **lst, t_token *new);
void	ft_tokclear(t_token **lst);
void	ft_tokprint(t_token *lst);
t_token	*cat_word(char **c_line, char *chr_set);
int		validation(t_token *token);

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include "../sources/libft/libft.h"

#endif

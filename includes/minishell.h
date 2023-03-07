/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:50:06 by microdri          #+#    #+#             */
/*   Updated: 2023/03/07 15:27:14 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/ioctl.h>
# include "../sources/libft/libft.h"

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_data_shell
{
	t_token	*tok_lst;
	char	**copy_env;
	char	**args;
}	t_data_shell;

void	parser_builtin(t_data_shell *data_shell);
void	ft_tokadd_back(t_token **lst, t_token *new);
void	ft_tokclear(t_token **lst);
void	ft_tokprint(t_token *lst);
void	handle_signals(int signum);
void	set_sig(void);
void	ft_pwd(void);
void	ft_echo(char **args);
void	ft_cd(char **path);
void	ft_exit(char **args);
void	ft_env(char **copy_env);
int		ft_toksize(t_token *lst);
int		ft_toksize_w(t_token *lst);
int		is_builtin(char *command);
int		execute_builtins(char *command, t_data_shell *data_shell);
int		validation(t_token *token);
char	**parser(t_data_shell *data_shell);
char	**ft_copy_env(char **env);
t_token	*ft_toknew(int type, char *str);
t_token	*ft_toklast(t_token *lst);
t_token	*lexer(char *c_line);
t_token	*cat_word(char **c_line, char *chr_set);
t_token	*cat_envvar(char **qt_str);
t_token	*cat_dollar(char *qt_str);
t_token	*special_chr(int type, char **c_line);

#endif

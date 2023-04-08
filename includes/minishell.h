/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:50:06 by microdri          #+#    #+#             */
/*   Updated: 2023/04/07 17:12:34 by microdri         ###   ########.fr       */
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
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include "../sources/libft/libft.h"

# define RESET 0
# define EXIT_EXEC 1

extern	int var_global;

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_sentence
{
	int					fd_in;
	int					fd_out;
	int					pid;
	char				**args;
	struct s_sentence	*next;	
	struct s_sentence	*prev;	
}	t_sentence;

typedef struct s_data_shell
{
	int			number_of_sentence;
	char		*input;
	char		**copy_env;
	t_token		*tok_lst;
	t_sentence	*sentence_list;
	int			n_pipes;
	int			n_redis;
	int			*fd_pipes;
	int			*fd_redis;
}	t_data_shell;


/*---------------init---------------*/
/*--------------handling------------*/
/*--------------verify--------------*/
/*--------------executions----------*/


void		open_heredoc(t_data_shell *data_shell, int i_fd);
void		execute_pipeline(t_data_shell *data_shell);
void		redirect(t_data_shell *data_shell);
void		r_input(t_data_shell shell, int i_fd);
void		tok_list_to_args(t_data_shell *data_shell);
void		r_output(t_data_shell shell, int i_fd);
void		remove_tok_nodes(t_token **lst, int n_nodes);
void		expand_str(char **str, char **env);
void		insert_envvar(char **str, char *env_var, int start, int end);
void		ft_tokadd_back(t_token **lst, t_token *new);
void		ft_tokclear(t_token **lst);
void		ft_tokprint(t_token *lst);
void		handle_signals(int signum);
void		set_sig(void);
void		ft_pwd(char **env_copy);
void		ft_echo(char **args, int fd_out);
void		ft_cd(char **path, char ***env);
void		ft_exit(char **args);
void		ft_env(char **copy_env);
void		ft_unset(t_data_shell *data_shell);
void		ft_export(char **input, char ***env);
void		free_copy_env(char **env_copy);
void		clear_memory(t_data_shell data_shell, int end_exec);
void		execute_cmd(t_data_shell *data_shell);
int			find_cmd(t_data_shell *data_shell);
void		verify_and_exec(t_data_shell *data_shell);
void		sentence_print(t_sentence *lst);
void		sentence_clear(t_sentence **lst);
void		sentence_add_back(t_sentence **lst, t_sentence *new);
void		message_error(char *msg, int exit_status);
void		config_pipes(t_data_shell *data_shell);
void		exec_pipes(t_data_shell *data_shell);
void		exec_sentence(t_data_shell *data_shell);
void		wait_sentences(t_data_shell *data_shell);
void		close_pipes(t_data_shell *data_shell);
int			count_pipes(t_token *tok_lst);
int			has_equal(char *str);
int			is_name_valid(char *str);
int			ft_toksize(t_token *lst);
int			ft_toksize_w(t_token *lst);
int			is_builtin(char *command);
int			execute_builtins(t_data_shell *data_shell);
int			validation(t_token *token);
int			verify_input(char *input);
char		*parse_arg(char *arg, char **env);
char		*get_envvar(char **env, char *var);
char		*find_path(char **cmd, char **envp);
char		*cat_envvar(char **arg, char *parsed_arg, char **env);
char		*cat_exitstatus(char **arg, char *parsed_arg);
void		parser(t_data_shell *data_shell);
char		**ft_copy_env(char **env);
t_token		*ft_toknew(int type, char *str);
t_token		*ft_toklast(t_token *lst);
t_token		*lexer(char *c_line);
t_token		*cat_word(char **c_line, char *chr_set);
t_token		*cat_dollar(char *qt_str);
t_token		*special_chr(int type, char **c_line);
t_sentence	*sentence_last(t_sentence *lst);
t_sentence	*sentence_new(char **args);

#endif

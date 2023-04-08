/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:51:58 by microdri          #+#    #+#             */
/*   Updated: 2023/04/08 10:57:27 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
int	var_global = 0;

void	init_values_struct(t_data_shell *data_shell, char *input)
{
	data_shell->sentence_list = NULL;
	data_shell->tok_lst = NULL;
	data_shell->fd_pipes = NULL;
	data_shell->fd_redis = NULL;
	if (input)
		data_shell->input = input;
	else
		data_shell->input = NULL;
}

int	main(int argc, char **argv, char **env)
{
	char			*input;
	t_data_shell	data_shell;

	(void) argc;
	(void) *argv;
	set_sig();
	data_shell.copy_env = ft_copy_env(env);
	while (42)
	{
		input = readline("microtano$: ");
		init_values_struct(&data_shell, input);
		data_shell.tok_lst = lexer(input);
		if (verify_input(input) == 0)
			break ;
//		ft_tokprint(data_shell.tok_lst);
		if (validation(data_shell.tok_lst) != 0)
			message_error("microtano: syntax error near unexpected token", 258);
//		printf("Erro lst_token\n"); //msg_error with exit_status
		else
		{
			parser(&data_shell);
//		sentence_print(data_shell.sentence_list);
			verify_and_exec(&data_shell);
		}
		clear_memory(data_shell, RESET);
	}
	clear_memory(data_shell, EXIT_EXEC);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:51:58 by microdri          #+#    #+#             */
/*   Updated: 2023/03/29 12:27:51 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_values_struct(t_data_shell *data_shell)
{
	data_shell->sentence_list = NULL;
	data_shell->tok_lst = NULL;
	data_shell->fd_pipes = NULL;
}

int	main(int argc, char **argv, char **env)
{
	char			*input;
	t_data_shell	data_shell;
	t_token			*header;

	(void) argc;
	(void) *argv;
	set_sig();
	header = NULL;	
	data_shell.copy_env = ft_copy_env(env);
	while (42)
	{
		input = readline("microtano$: ");
		init_values_struct(&data_shell);
		header = lexer(input);
		data_shell.tok_lst = header;
		if (verify_input(input) == 0)
			break ;
//		ft_tokprint(data_shell.tok_lst);
		parser(&data_shell);
//		sentence_print(data_shell.sentence_list);
		data_shell.tok_lst = header;
		verify_and_exec(&data_shell);
//		data_shell.tok_lst = header;
		clear_memory(input, data_shell);
		header = NULL;
	}
	clear_history();
	free_copy_env(&data_shell);
	data_shell.tok_lst = header;
	clear_memory(input, data_shell);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:51:58 by microdri          #+#    #+#             */
/*   Updated: 2023/03/09 17:27:49 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Do a functions that free copy_env! taken from line 44 to 49!

int	main(int argc, char **argv, char **env)
{
	char			*input;
	t_data_shell	data_shell;
	t_token			*header;

	(void) argc;
	(void) *argv;
	set_sig();
	data_shell.tok_lst = NULL;
	data_shell.copy_env = ft_copy_env(env);
	while (42)
	{
		input = readline("microtano$: ");
		if (input != NULL && input[0] != 0)
			add_history(input);
		if (input == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}
		header = lexer(input);
		data_shell.tok_lst = header;
		parser(&data_shell);
		data_shell.tok_lst = header;
		clear_memory(input, data_shell);
	}
	clear_history();
	free_copy_env(&data_shell);
	data_shell.tok_lst = header;
	clear_memory(input, data_shell);
	return (0);
}

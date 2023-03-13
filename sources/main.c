/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:51:58 by microdri          #+#    #+#             */
/*   Updated: 2023/03/13 17:50:12 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_values_struct(t_data_shell *data_shell)
{
	data_shell->sentence_list = malloc(sizeof(t_sentence));
	if (!data_shell->sentence_list)	
		printf("error with sentence_list malloc\n");
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
		if (verify_input(input) == 0)
			break ;
		header = lexer(input);
		data_shell.tok_lst = header;
		parser(&data_shell);
		data_shell.tok_lst = header;
		clear_memory(input, data_shell);
		header = NULL;
	}
	clear_history();
	free_copy_env(&data_shell);
	data_shell.tok_lst = header;
	clear_memory(input, data_shell);
}

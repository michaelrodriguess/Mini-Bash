/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:51:58 by microdri          #+#    #+#             */
/*   Updated: 2023/03/06 11:51:52 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char			*input;
	t_data_shell	data_shell;
	t_token			*head;

	(void) argc;
	(void) *argv;
	set_sig();
	data_shell.tok_lst = NULL;
	data_shell.env = env;
	while (42)
	{
		input = readline("microtano$: ");
		if (ft_strcmp(input, "exit") == 0 || input == NULL)
		{
			write(1, "exit\n", 5);
			clear_history();
			free(input);
			ft_tokclear(&head);
			break ;
		}
		if (input[0] != 0)
			add_history(input);
		head = lexer(input);
		data_shell.tok_lst = head;
		parser(&data_shell);
		free(input);
		ft_tokclear(&head);
	}
	return (0);
}

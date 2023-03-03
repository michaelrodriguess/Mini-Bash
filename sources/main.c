/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:51:58 by microdri          #+#    #+#             */
/*   Updated: 2023/03/02 11:31:59 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	test_builtins(char *input)
{
	char *test_set[] = {"test", "echo", "this", NULL};
	char *test_set2[] = {"-n", "test", "echo", "this", "with -n optin", NULL};

	if (!ft_strcmp(input, "pwd"))
		ft_pwd();
	if (!ft_strcmp(input, "echo"))
	{
		ft_echo(test_set);
		ft_echo(test_set2);
	}
}

int	main(void)
{
	char	*input;

	set_sig();
	while (42)
	{
		input = readline("microtano$: ");
		if (ft_strcmp(input, "exit") == 0 || input == NULL)
		{
			write(1, "exit\n", 5);
			clear_history();
			break ;
		}
		if (input[0] != 0)
			add_history(input);
		test_builtins(input);
		free(input);
	}
	return (0);
}

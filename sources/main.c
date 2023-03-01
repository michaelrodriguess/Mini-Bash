/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:51:58 by microdri          #+#    #+#             */
/*   Updated: 2023/03/01 18:07:33 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*input;

	while (42)
	{
		input = readline("microtano$: ");
		if (ft_strcmp(input, "exit") == 0)
		{
			write(1, "exit\n", 5);
			clear_history();
			break ;
		}
		if (input[0] != 0)
			add_history(input);
		free(input);
	}
	return (0);
}

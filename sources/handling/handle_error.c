/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:48:07 by microdri          #+#    #+#             */
/*   Updated: 2023/03/11 20:50:16 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	verify_input(char *input)
{
	if (input != NULL && input[0] != 0)
		add_history(input);
	if (ft_strcmp("exit", input) == 0 || input == NULL)
	{
		write(2, "exit\n", 5);
		return (0);
	}
	return (1);
}

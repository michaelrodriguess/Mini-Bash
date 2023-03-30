/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:20:34 by microdri          #+#    #+#             */
/*   Updated: 2023/03/30 17:24:33 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_signals(int signum)
{
	if (signum == SIGINT)
	{
		if (RL_ISSTATE(RL_STATE_READCMD))
		{
			ioctl(1, TIOCSTI, "\n");
		}
		else
		{
			write(1, "\n", 1);
		}
		rl_on_new_line();
		rl_replace_line("", 0);
		var_global = 128 + SIGINT;
	}
}

void	set_sig(void)
{
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
}

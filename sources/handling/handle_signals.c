/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:20:34 by microdri          #+#    #+#             */
/*   Updated: 2023/04/08 17:56:48 by microdri         ###   ########.fr       */
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
		g_var_global = 1;
	}
}

void	handle_signals_heredoc(int signum)
{
	if (signum == SIGINT)
		g_var_global = 1;
	if (RL_ISSTATE(RL_STATE_READCMD))
	{
		ioctl(1, TIOCSTI, "\n");
	}
}

void	set_sig(void)
{
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
}

void	child_sig_def(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	set_sig_heredoc(void)
{
	signal(SIGINT, handle_signals_heredoc);
}

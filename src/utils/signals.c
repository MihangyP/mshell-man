/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 10:01:47 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 17:14:14 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	setup_signals_heredoc(struct sigaction *sa)
{
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	sa->sa_handler = handler_sigint_heredoc;
	sigaction(SIGINT, sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	handler_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal = sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	handler_sigint(int signum)
{
	if (signum == SIGINT)
	{
		set(130);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	setup_signals(t_mshell *mshell)
{
	sigemptyset(&mshell->sa_sigquit.sa_mask);
	sigemptyset(&mshell->sa.sa_mask);
	sigemptyset(&mshell->sa_ignore.sa_mask);
	mshell->sa.sa_handler = handler_sigint;
	mshell->sa.sa_flags = 0;
	sigaction(SIGINT, &mshell->sa, NULL);
	mshell->sa_ignore.sa_handler = SIG_IGN;
	mshell->sa_sigquit.sa_flags = 0;
	mshell->sa_ignore.sa_flags = 0;
	mshell->sa_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &mshell->sa_sigquit, NULL);
}

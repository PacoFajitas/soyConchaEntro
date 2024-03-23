/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlopez-i <mlopez-i@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:04:23 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/23 14:15:39 by mlopez-i         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_signals(int mode)
{
	struct sigaction	signal;

	signal.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&signal.sa_mask);
	signals_print_handler();
	if (mode == 1)
		signal.sa_sigaction = norm_handler;
	else if (mode == 2)
		signal.sa_sigaction = ninter_handler;
	else if (mode == 3)
		signal.sa_sigaction = heredoc_handler;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
	return (0);
}

void	do_sigign(int signum)
{
	struct sigaction	signal;

	signal.sa_handler = SIG_IGN;
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	if (sigaction(signum, &signal, NULL) < 0)
		exit (1);
}

void	norm_handler(int sig, siginfo_t *data, void *non_used_data)
{
	(void) data;
	(void) non_used_data;
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_sig = 1;
	}
	return ;
}

void	signals_print_handler(void)
{
	struct termios	tc;

	tcgetattr(0, &tc);
	tc.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &tc);
}

void	heredoc_handler(int sig, siginfo_t *data, void *non_used_data)
{
	(void) data;
	(void) non_used_data;
	if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("\n", 1);
		g_sig = 1;
		exit (1);
	}
	return ;
}

void	ninter_handler(int sig, siginfo_t *data, void *non_used_data)
{
	(void) data;
	(void) non_used_data;
	if (sig == SIGINT)
	{
		g_sig = 130;
		exit(130);
	}
	else if (sig == SIGQUIT)
	{
		g_sig = 131;
		exit(130);
	}
	return ;
}
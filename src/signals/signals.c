/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:04:23 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/22 11:00:44 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//   type 0 = general
//   type 1 = bloqueantes
void	ft_general_handler(int type)
{
	if (type == 0)
	{
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
	}
	if (type == 1)
	{
		signal(SIGINT, ft_sigint_exec);
		signal(SIGQUIT, ft_sigquit);
		signal(SIGTERM, SIG_IGN);
	}
}

void	ft_sigquit(int sig)
{
	(void)sig;
	rl_on_new_line();
}

void	ft_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
void	ft_sigint_exec(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
}
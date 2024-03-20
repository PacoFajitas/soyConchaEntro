/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 22:56:41 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/20 09:56:17 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_check_flag(char *args, int found)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 1;
	while (args[i] && n_flag == 1)
	{
		if (args[i] != 'n' && found == 0)
			n_flag = 0;
		else if (args[i] != 'n' && found == 1)
			return (0);
		i++;
	}
	return (n_flag);
}

int	ft_echo(t_pipe *p)
{
	int		n_flag;
	int		i;

	n_flag = 0;
	i = 1;
	if (p->out == -3)
		p->out = 1;
	if (!p->cmds[i])
	{
		ft_putstr_fd("\n", p->out);
		return (0);
	}
	while (p->cmds[i] && p->cmds[i][0] == '-' && p->cmds[i][1] != '-')
	{
		if (ft_check_flag(p->cmds[i], n_flag) == 1)
		{
			n_flag = 1;
			i++;
		}
		else
			break ;
	}
	while (p->cmds[i])
	{
		ft_putstr_fd(p->cmds[i], p->out);
		if (p->cmds[i + 1])
			ft_putstr_fd(" ", p->out);
		i++;
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", p->out);
	return (0);
}

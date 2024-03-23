/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 06:50:57 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/23 16:57:20 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

long long int	ft_atol_sh(char *str, int *err, int i)
{
	int			sign;
	long long	number;

	sign = 1;
	number = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (number * 10 > 922337203685477580 || number < -922337203685477588)
		{
			*err = 1;
			break ;
		}
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	return ((number *= sign));
}

int	ft_isnum(char *str, int i, int ret)
{
	if (ft_strlen(str) == 0)
		return (0);
	while (str[i] == '-')
		i++;
	if (!str[i] && i == 2)
		return (1);
	else if (str[i] && i == 2)
		return (0);
	else if (!str[i])
		return (0);
	if ((str[i] == '+' && i > 0))
		return (0);
	else if (str[i] == '+' && i == 0)
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			ret = 0;
		i++;
	}
	return (ret);
}

int	ft_count_args(t_pipe *p)
{
	int	i;

	i = 0;
	while (p->cmds[i])
		i++;
	return (i);
}

int	ft_exit_b(t_pipe *p, t_data *data, int num, int err)
{
	if (p->cmds[1])
	{
		ft_putstr_fd("exit\n", p->out);
		num = ft_atol_sh(p->cmds[1], &err, 0);
		if (ft_count_args(p) > 2)
			return (ft_exit_error(NULL, "too many arguments"));
		if (err != 0 || ft_isnum(p->cmds[1], 0, 1) == 0)
		{
			ft_exit_error(p->cmds[1], "numeric argument required");
			num = 255;
		}
		else
			num = ft_atol_sh(p->cmds[1], &err, 0);
		data->off = 1;
	}
	else
	{
		data->off = 1;
		num = data->exit;
		ft_putstr_fd("exit", p->out);
	}
	return (num);
}

int	ft_exit(t_data *data)
{
	int	exit_status;
	int	print;

	print = data->off;
	exit_status = data->exit;
	ft_clean_all_data(data);
	if (!print)
		ft_putstr_fd("exit\n", 1);
	return (exit_status);
}

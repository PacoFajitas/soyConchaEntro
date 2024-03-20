/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlopez-i <mlopez-i@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 22:30:27 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/20 20:22:04 by mlopez-i         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_check_open(t_pipe *p, t_fd *fd, int prev)
{
	if (p->in >= 0 && (fd->type == HDOC || fd->type == REDIRIN) \
		&& prev != HDOC)
	{
		close(p->in);
		p->in = -3;
	}
	if (p->out >= 0 && (fd->type == REDIROUT || fd->type == APPEND))
	{
		close(p->out);
		p->out = -3;
	}
}

int	ft_check_open_builtin(t_data *data, t_pipe *p, t_fd *fd)
{
	if (p->in < 0 && (fd->type == HDOC || fd->type == REDIRIN))
	{
		perror(fd->str);
		data->exit = 1;
		return (0);
	}
	if (p->out < 0 && (fd->type == REDIROUT || fd->type == APPEND))
	{
		perror(fd->str);
		data->exit = 1;
		return (0);
	}
	return (1);
}

int	ft_open_builtin(t_data *data, t_pipe *p, t_fd *fd, int prev)
{
	int	x;

	x = data->p->in;
	while (fd)
	{
		ft_check_open(p, fd, prev);
		if (fd->type == HDOC)
			p->in = fd->fd;
		else if (!fd->str || *fd->str == '\0')
			return (ft_error_ret(data, NULL, "No such file or directory\n", 1));
		else if (fd->type == REDIRIN)
			p->in = open(fd->str, O_RDONLY);
		else if (fd->type == REDIROUT)
			p->out = open(fd->str, O_TRUNC | O_CREAT | O_RDWR, 0666);
		else if (fd->type == APPEND)
			p->out = open(fd->str, O_APPEND | O_CREAT | O_RDWR, 0666);
		if (!ft_check_open_builtin(data, p, fd))
			return (0);
		prev = fd->type;
		fd = fd->next;
	}
	return (1);
}

int	ft_check_open_file(t_data *data, t_pipe *p, t_fd *fd)
{
	if (p->in < 0 && (fd->type == HDOC || fd->type == REDIRIN))
	{
		data->exit = 1;
		perror(fd->str);
		return (0);
	}
	if (p->out < 0 && (fd->type == REDIROUT || fd->type == APPEND))
	{
		data->exit = 1;
		perror(fd->str);
		return (0);
	}
	return (1);
}

void	ft_open_file(t_data *data, t_pipe *p, t_fd *fd, int prev)
{
	while (fd)
	{
		ft_check_open(p, fd, prev);
		if (fd->type == HDOC)
			p->in = fd->fd;
		else if (!fd->str || *fd->str == '\0')
			exit(ft_error_exit(data, NULL, "No such file or directory\n", 1));
		else if (fd->type == REDIRIN)
			p->in = open(fd->str, O_RDONLY);
		else if (fd->type == REDIROUT)
			p->out = open(fd->str, O_RDWR | O_CREAT
					| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if (fd->type == APPEND)
			p->out = open(fd->str, O_APPEND | O_CREAT | O_RDWR, 0666);
		if (!ft_check_open_file(data, p, fd))
			exit(data->exit);
		prev = fd->type;
		fd = fd->next;
	}
}

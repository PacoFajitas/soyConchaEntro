/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 22:30:27 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/20 10:07:25 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_check_builtin(t_pipe *p)
{
	if (!p || !p->cmds || !p->cmds[0])
		return (0);
	else if (ft_strcmp(p->cmds[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(p->cmds[0], "cd") == 0)
		return (2);
	else if (ft_strcmp(p->cmds[0], "pwd") == 0)
		return (3);
	else if (ft_strcmp(p->cmds[0], "export") == 0)
		return (4);
	else if (ft_strcmp(p->cmds[0], "unset") == 0)
		return (5);
	else if (ft_strcmp(p->cmds[0], "env") == 0)
		return (6);
	else if (ft_strcmp(p->cmds[0], "exit") == 0)
		return (7);
	return (0);
}

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
		prev = fd->type;
		fd = fd->next;
	}
	return (1);
}

int	ft_check_access_file(char *str, int mode)
{
	
	if(mode == 1)
	{
		if (access(str, F_OK) == -1)
			perror(str);
		if (access(str, R_OK) == -1)
			perror(str);
	}
	else
	{
		if(access(str, F_OK) == -1)
			perror(str);
		if (access(str, W_OK) == -1)
			perror(str);
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
			p->out = open(fd->str, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP
			| S_IROTH);
		else if (fd->type == APPEND)
			p->out = open(fd->str, O_APPEND | O_CREAT | O_RDWR, 0666);
		if (p->in < 0 && (fd->type == HDOC || fd->type == REDIRIN))
		{
			data->exit = 1;
			perror(fd->str);
			exit(data->exit);
		}
		if (p->out < 0 && (fd->type == REDIROUT || fd->type == APPEND))
		{
			data->exit = 1;
			perror(fd->str);
			exit(data->exit);
		}
		prev = fd->type;
		fd = fd->next;
	}
}

void	exit_status(t_data	*data, int j)
{
	while (++j <= data->pipes)
	{
		if (data->pid == wait(&data->status))
		{
			if (WIFEXITED(data->status))
				data->exit = WEXITSTATUS(data->status);
			else if (WIFSIGNALED(data->status))
			{
				if (WTERMSIG(data->status) == SIGINT)
				{
					printf("\n");
					data->exit = 130;
				}
				else if (WTERMSIG(data->status) == SIGQUIT)
				{
					data->exit = 131;
					printf("Quit: 3\n");
				}
			}
		}
	}
}

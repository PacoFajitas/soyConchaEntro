/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 22:30:18 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/22 13:17:12 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
// echo aaaa > a | ls | echo bbbbb > b | cat < b
int	ft_execute_builtin(t_data *data, t_pipe *p)
{
	if (!data->pipes && !ft_open_builtin(data, p, p->fds, -1))
		return (1);
	if (p->builtin == 1)
		return (ft_echo(p, 0, 1));
	else if (p->builtin == 2)
		return (ft_cd(data, p, &data->env, &data->export));
	else if (p->builtin == 3)
		ft_pwd(p, data);
	else if (p->builtin == 4)
		return (ft_export(&data, p, 1));
	else if (p->builtin == 5)
		return (ft_unset(p, &data));
	else if (p->builtin == 6)
		return (ft_print_env(&data->env, p));
	else if (p->builtin == 7)
		return (ft_exit_b(p, data, 0, 0));
	return (0);
}

void	ft_check_access(t_data *data, char **cmd, t_pipe *p)
{
	if (!cmd || !(*cmd))
		exit(0);
	else if (!(**cmd))
		exit(127);
	if (ft_strchr(cmd[0], '/'))
	{
		if (access(cmd[0], F_OK) == 0)
		{
			if (access(cmd[0], X_OK) != 0)
				exit(126);
			p->path = cmd[0];
		}
		else
			exit(ft_error_exit(data, cmd[0], "No such file or directory", 127));
	}
}

void	ft_child_process(t_data *data, t_pipe *p, int last)
{
	if (!last)
	{
		close(data->fd[0]);
		data->fd[0] = -3;
	}
	ft_open_file(data, p, p->fds, -1);
	if (p->builtin)
	{
		data->exit = ft_execute_builtin(data, p);
		exit(data->exit);
	}
	ft_check_access(data, p->cmds, p);
	ft_redir(p);
	if (!p->path && !p->builtin && p->cmds && p->cmds[0])
		ft_error_exit(data, p->cmds[0], "command not found", 127);
	if (execve(p->path, p->cmds, ft_env_to_array(&data->env)) == -1)
		ft_error_exit(data, NULL, NULL, 126);
}

int	ft_last_process(t_data *data, t_pipe *p)
{
	if (!data->pipes && data->p->builtin)
	{
		data->exit = ft_execute_builtin(data, p);
		return (data->exit);
	}
	data->pid = fork();
	if (data->pid < 0)
		exit(1);
	else if (data->pid == 0)
		ft_child_process(data, p, 1);
	if (data->pipes && data->p->in >= 0)
		close(p->in);
	if (data->fd[0] >= 0)
		 close(data->fd[0]);
	return (1);
}

/* 	0 si cagaste 
	fd == 0 es reader
  	fd == 1 es writer */
int	ft_executor(t_data *data, t_pipe *p)
{
	int	i;

	i = -1;
	while (++i < data->pipes)
	{
		if (pipe(data->fd) == -1)
			return (ft_error_ret(data, "pipe", "error", -1));
		p->out = data->fd[1];
		data->pid = fork();
		if (data->pid < 0)
			return (ft_error_ret(data, "pipe", "error", -1));
		if (data->pid == 0)
			ft_child_process(data, p, 0);
		close (data->fd[1]);
		if (p->in >= 0)
			close (p->in);
		p = p->next;
		p->in = data->fd[0];
	}
	data->exit = ft_last_process(data, p);
	exit_status(data, -1);
	if (p->cmds && p->cmds[0] && !ft_strcmp(p->cmds[0], "test"))
		data->exit = 1;
	return (data->off);
}

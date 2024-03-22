/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:15:50 by mlopez-i          #+#    #+#             */
/*   Updated: 2024/03/22 19:33:16 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir(t_pipe *p)
{
	if (p->in >= 0)
	{
		if (dup2(p->in, STDIN_FILENO) < 0)
			exit(1);
		close(p->in);
		p->in = -3;
	}
	if (p->out >= 0)
	{
		if (dup2(p->out, STDOUT_FILENO) < 0)
			exit(1);
		close(p->out);
		p->out = -3;
	}
}

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

int	ft_check_access_file(char *str, int mode)
{
	if (mode == 1)
	{
		if (access(str, F_OK) == -1)
			perror(str);
		if (access(str, R_OK) == -1)
			perror(str);
	}
	else
	{
		if (access(str, F_OK) == -1)
			perror(str);
		if (access(str, W_OK) == -1)
			perror(str);
	}
	return (1);
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

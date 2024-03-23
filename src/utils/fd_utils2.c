/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 06:51:37 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/23 16:53:36 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cosas_hd(int pid, t_data *data, t_fd *new, int hd[2])
{
	int		status;

	if (pid == 0)
	{
		init_signals(3);
		ft_save_hd(new->str, &data->env, hd);
	}
	else
	{
		waitpid(pid, &status, 0);
		new->fd = hd[0];
		close(hd[1]);
		if (WTERMSIG(status) == SIGINT)
		{
			ft_putstr_fd("\n", 1);
			return (0);
		}
	}
	return (1);
}

/*	es keyword haya espacio o no!!	*/
/*	desde el syntax checker pasarle la keyword!	*/
int	ft_heredoc(t_data *data, char *key)
{
	t_fd	*new;
	pid_t	pid;
	int		hd[2];

	new = malloc(sizeof(t_fd));
	if (!new)
		return (ft_error_ret(data, NULL, "malloc error", 134));
	init_fd(new, HDOC, -3, key);
	ft_add_fd(&data->fds, new);
	pipe(hd);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (!ft_cosas_hd(pid, data, new, hd))
		return (0);
	return (1);
}

void	ft_free_fds(t_fd **fd)
{
	t_fd	*tmp;

	while (*fd)
	{
		tmp = (*fd)->next;
		if ((*fd)->str)
			free((*fd)->str);
		free(*fd);
		*fd = tmp;
	}
}

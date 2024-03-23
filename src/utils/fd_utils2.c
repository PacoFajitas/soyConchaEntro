/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlopez-i <mlopez-i@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 06:51:37 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/23 14:21:34 by mlopez-i         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_print_fds(t_fd *fd)
{
	t_fd	*fd1;

	fd1 = fd;
	dprintf(1, "hola\n");
	while (fd1)
	{
		if (fd1->str)
			dprintf(1, "fd1.str::%s\n", fd1->str);
		dprintf(1, "ei\n");
		fd1 = fd1->next;
	}	
}

/*	es keyword haya espacio o no!!	*/
/*	desde el syntax checker pasarle la keyword!	*/
int	ft_heredoc(t_data *data, char *key)
{
	t_fd	*new;
	pid_t	pid;
	int		status;
	int		hd[2];

	new = malloc(sizeof(t_fd));
	if (!new)
		return (ft_error_ret(data, NULL, "malloc error", 134));
	init_fd(new, HDOC, -3, key);
	ft_add_fd(&data->fds, new);
	pipe(hd);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		init_signals(3);
		dprintf(1, "ei g_sig :: %i\n", g_sig);
		ft_save_hd(key, &data->env, hd);
	}
	else
	{
		waitpid(pid, &status, 0);
		new->fd = hd[0];
		close(hd[1]);
		dprintf(1, "holi g_sig :: %i\n", g_sig);
		if (WTERMSIG(status) == SIGINT)
		{
			dprintf(1, "hola\n");
			ft_putstr_fd("\n", 1);
			return (0);
		}
	}
	dprintf(1, "holis g_sig :: %i\n", g_sig);
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

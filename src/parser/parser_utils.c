/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:44:40 by mlopez-i          #+#    #+#             */
/*   Updated: 2024/03/18 13:56:36 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_init_pipe(t_pipe *p)
{
	p->cmds = NULL;
	p->path = NULL;
	p->in = -3;
	p->out = -3;
	p->builtin = 0;
	p->fds = NULL;
	p->next = NULL;
}

void	ft_add_pipe(t_pipe **pipe, t_pipe *new)
{
	t_pipe	*tmp;

	if (!(*pipe))
	{
		(*pipe) = new;
		return ;
	}
	tmp = *pipe;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_free_pipe(t_pipe **p)
{
	t_pipe	*tmp;

	while (*p)
	{
		tmp = (*p)->next;
		if ((*p)->cmds)
			ft_free_array((*p)->cmds);
		if ((*p)->path)
			free((*p)->path);
		free(*p);
		*p = tmp;
	}
}

void	ft_print_pipes(t_pipe **p)
{
	t_pipe	*pipe;
	int		i;

	pipe = *p;
	if (!pipe)
	{
		dprintf(1, "no pipes\n");
		return ;
	}
	while (pipe)
	{
		if (!pipe->cmds)
			dprintf(1, "No comands\n");
		if (pipe->cmds)
		{
			// dprintf(1, "holi\n");
			i = -1;
			while (pipe->cmds[++i])
				dprintf(1, "CMDS:%s&\n", pipe->cmds[i]);
		}
		if (pipe->in)
			dprintf(1, "pipe in:%i\n", pipe->in);
		// if (pipe->path)
		// 	dprintf(1, "PATH:%s&\n", pipe->path);
		if (pipe && pipe->fds && pipe->fds->str)
			dprintf(1, "FD STR:%s&\n", pipe->fds->str);
		// if (pipe->fds && pipe->fds->next && pipe->fds->next->str)
		// 	dprintf(1, "FD STR NEXT:%s&\n", pipe->fds->next->str);
		pipe = pipe->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlopez-i <mlopez-i@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:44:40 by mlopez-i          #+#    #+#             */
/*   Updated: 2024/03/20 19:46:46 by mlopez-i         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

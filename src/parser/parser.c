/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:46:06 by mlopez-i          #+#    #+#             */
/*   Updated: 2024/03/20 13:41:40 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parse_redirs(t_data *data, t_token **tmp)
{
	t_fd	*new;

	
	new = malloc(sizeof(t_fd));
	if (!new)
		return (0);
	new->type = (*tmp)->type;
	new->next = NULL;
	new->fd = -3;
	(*tmp) = (*tmp)->next;
	while (*tmp && (*tmp)->type == 0)
		*tmp = (*tmp)->next;
	if (*tmp && (*tmp)->content  && new->type != HDOC)
	{
		new->str = ft_strdup((*tmp)->content);
		ft_add_fd(&(data)->fds, new);
		if (!new->str)
			return (0); //return error exit malloc(?)
	}
	if (*tmp && (*tmp)->content && new->type == HDOC)
		ft_heredoc(data, (*tmp)->content);
	//llamar func signals
	*tmp = (*tmp)->next;
	return (1);
}

int	parse_cmds(t_data *data, t_pipe *p, t_token **tmp)
{
	p->cmds = ft_token_to_array(tmp, p->cmds);
	if (!p->cmds)
		return (0);
	p->path = ft_get_cmd_path(&data->env, p->cmds[0]);
	p->builtin = ft_check_builtin(p);
	// if (!p->path && !p->builtin)
	// {
	// 	ft_putstr_fd("minishell: ", 2);
	// 	ft_putstr_fd(p->cmds[0], 2);
	// 	ft_putstr_fd(": command not found\n", 2);
	// 	data->error = 127;
	// 	return (0);
	// }
	while (*tmp && (*tmp)->type < PIPE)
		*tmp = (*tmp)->next;
	return (1);
}
/*	Duplicar fd en p->fds
	Borrar nodos duplicados	*/
int	ft_skip_redirs(t_token **tmp, t_pipe *p, t_fd **fd)
{
	t_fd	*new;
	int	type;

	type = (*tmp)->type;
	if ((*tmp) && ((*tmp)->type > 4 && (*tmp)->type < 9))
	{
		(*tmp) = (*tmp)->next;
	}
	while ((*tmp) && (*tmp)->type == 0)
	{
		(*tmp) = (*tmp)->next;
	}
	if ((*tmp) && ((*tmp)->type >= 1 && (*tmp)->type <= 3))
	{
		new = malloc(sizeof(t_fd));
		// printf("%s\n",(*tmp)->content);
		init_fd(new, type, (*fd)->fd);
		new->str = ft_strdup((*fd)->str);
		// p->fds = new;
		ft_add_fd(&p->fds, new);
		*fd = (*fd)->next;
		(*tmp) = (*tmp)->next;
		return (1);
	}
	return (0);
}

int	ft_parser(t_data *data, t_token **token)
{
	t_pipe	*newp;
	int		ret;
	t_token	*tmp;
	t_fd	*fd;

	tmp = *token;
	ret = 1;
	fd = data->fds;
	while (tmp)
	{
		newp = malloc(sizeof(t_pipe));
		ft_init_pipe(newp);
		while (tmp && tmp->type != PIPE)
		{
			if (tmp->type > 4 && tmp->type <= 8)
				ret = ft_skip_redirs(&tmp, newp, &fd);
			else if (tmp->type > SPACES && tmp->type < PIPE)
				ret = parse_cmds(data, newp, &tmp);
			else
				tmp = tmp->next;
			if (!tmp || !ret)
				break ;
		}
		ft_add_pipe(&data->p, newp);
		if (tmp)
			tmp = tmp->next;
	}
	// dprintf(1, "printing on parser\n");
	// ft_print_pipes(&data->p);
	return (ret);
}

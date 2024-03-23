/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlopez-i <mlopez-i@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:59:24 by mlopez-i          #+#    #+#             */
/*   Updated: 2024/03/22 21:47:39 by mlopez-i         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_syntax_char(t_token *tmp)
{
	if (tmp->type == PIPE)
		return ("|");
	else if (tmp->type == HDOC)
		return ("<<");
	else if (tmp->type == REDIROUT)
		return (">");
	else if (tmp->type == APPEND)
		return (">>");
	else if (tmp->type == REDIRIN)
		return ("<");
	return (NULL);
}

int	ft_print_syntax_error(t_data *data, t_token *tmp, int error, int exit)
{
	ft_putstr_fd("minihell😭🔥👿: syntax error near unexpected token `", 2);
	if (error == 1)
		ft_putstr_fd("|", 2);
	if (error == 2)
		ft_putstr_fd("newline", 2);
	if (error == 3)
		ft_putstr_fd(ft_syntax_char(tmp), 2);
	ft_putstr_fd("\'\n", 2);
	data->exit = exit;
	return (0);
}

int	ft_syntax_pipe(t_token *tmp, t_data *data)
{
	if (tmp->type == 4)
	{
		if (!tmp->prev || !tmp->next)
			return (ft_print_syntax_error(data, tmp, 1, 258));
		if (tmp->prev && tmp->next)
		{
			if (tmp->prev->type >= 4 && tmp->prev->type <= 8)
				return (ft_print_syntax_error(data, tmp, 1, 258));
			if (tmp->prev->type == 0)
			{
				if (!tmp->prev->prev)
					return (ft_print_syntax_error(data, tmp, 1, 258));
				if (tmp->prev->prev->type >= 5 && tmp->prev->prev->type <= 8)
					return (ft_print_syntax_error(data, tmp, 1, 258));
			}
		}
	}
	return (1);
}

int	ft_syntax_redirs(t_token **tmp)
{
	if ((*tmp)->next && (*tmp)->next->type == 0 && !(*tmp)->next->next)
		return (0);
	if ((*tmp)->next && (*tmp)->next->type == 0 && (*tmp)->next->next
		&& ((*tmp)->next->next->type < 1 || (*tmp)->next->next->type > 3))
		return (0);
	if ((*tmp)->next && (*tmp)->next->type != 0)
		return (0);
	if ((*tmp)->type == 6 && (*tmp)->next && (*tmp)->next->type == 8)
		return (0);
	return (1);
}

int	ft_syntax_error(t_data *data, t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (!ft_syntax_pipe(tmp, data))
			return (0);
		if (!tmp->next && (tmp->type >= 5 && tmp->type <= 8))
			return (ft_print_syntax_error(data, tmp, 2, 258));
		if (tmp->type > 4 && tmp->type < 9)
		{
			if (!ft_syntax_redirs(&tmp))
				return (ft_print_syntax_error(data, tmp, 3, 258));
			if (!parse_redirs(data, &tmp))
				return (ft_print_syntax_error(data, tmp, 2, 258));
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (1);
}

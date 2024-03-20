/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlopez-i <mlopez-i@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 04:59:41 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/20 20:42:37 by mlopez-i         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_expand_content(t_data *data, t_token *tmp, int *exp)
{
	if (tmp->type == 1)
		return (ft_expand_string(tmp->content, data, 0, exp));
	else if (tmp->type == 2)
		return (ft_strdup(tmp->content));
	else if (tmp->type == 3)
		return (ft_expand_dquoted(tmp->content, data, 0));
	else
		return (NULL);
}

t_token	*ft_expan(t_token **token, t_data *data, int type, int *exp)
{
	t_token	*tmp;
	t_token	*new_lst;
	t_token	*new;
	char	*content;

	tmp = *token;
	new_lst = NULL;
	while (tmp)
	{
		content = ft_expand_content(data, tmp, exp);
		type = tmp->type;
		new = ft_new_token(content, type, *exp);
		if (!new)
			return (NULL);
		ft_add_token(&new_lst, new);
		*exp = 0;
		tmp = tmp->next;
	}
	ft_free_token(token);
	return (new_lst);
}

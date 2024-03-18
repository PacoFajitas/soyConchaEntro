/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 04:59:41 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/17 06:28:05 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_expan(t_token **token, t_data *data, int type, int *exp)
{
	t_token	*tmp;
	t_token *new_lst;
	t_token *new;
	char 	*content;
	
	tmp = *token;
	new_lst = NULL;
	while (tmp)
	{
		if(tmp->type == 1)
			content = ft_expand_string(tmp->content, data, 0, exp);
		else if (tmp->type == 2)
			content = ft_strdup(tmp->content);
		else if (tmp->type == 3)
			content = ft_expand_dquoted(tmp->content, data, 0, exp);
		else
			content = NULL;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:33:42 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/17 16:14:21 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_unset_node(t_env **env, int i)
{
	t_env	*tmp;
	t_env	*tmp2;
	int		j;

	j = 0;
	tmp = *env;
	if (i == 0)
	{
		*env = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		return ;
	}
	while (j < i - 1)
	{
		tmp = tmp->next;
		j++;
	}
	tmp2 = tmp->next;
	tmp->next = tmp2->next;
	tmp2->next = NULL;
	free(tmp2->key);
	free(tmp2->value);
	free(tmp2);
}

int	ft_unset(t_pipe *p, t_data **data)
{
	t_env	*tmp;
	char	*key;
	int		i;

	i = 0;
	if(!p->cmds[1])
		return(1);
	tmp = (*data)->env;
	key = p->cmds[1];
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			ft_unset_node(&(*data)->env, i);
			break ;
		}
		tmp = tmp->next;
		i++;
	}
	tmp = (*data)->export;
	i = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			ft_unset_node(&(*data)->export, i);
			break ;
		}
		tmp = tmp->next;
		i++;
	}
	return (1);
}

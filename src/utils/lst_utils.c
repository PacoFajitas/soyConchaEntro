/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlopez-i <mlopez-i@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 01:16:13 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/20 21:34:26 by mlopez-i         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_token_to_array2(char **cmds, int *i)
{
	char	**array;
	int		j;

	j = *i;
	array = ft_calloc((j + 1), sizeof(char *));
	if (!array)
		return (NULL);
	j = 0;
	if (cmds && cmds[0])
	{
		while (cmds[j])
		{
			array[j] = ft_strdup(cmds[j]);
			if (!array[j])
			{
				ft_free_array(cmds);
				return (ft_free_array(array));
			}
			j++;
		}
		ft_free_array(cmds);
	}
	*i = j;
	return (array);
}

char	**ft_token_to_array(t_token **token, char **cmds)
{
	char	**array;
	int		i;
	t_token	*tmp;

	i = 0;
	while (cmds && cmds[i])
		i++;
	tmp = *token;
	while (tmp)
	{
		if (tmp->type != 0 && tmp->type != 1 \
			&& tmp->type != 2 && tmp->type != 3)
			break ;
		if (tmp->expanded == 1 && tmp->type == STRING && tmp->content)
			i += ft_count_spaces(tmp->content);
		i++;
		tmp = tmp->next;
	}
	array = ft_token_to_array2(cmds, &i);
	if (!array)
		return (NULL);
	tmp = *token;
	return (ft_aux_array(tmp, array, i));
}

char	**ft_aux_array_if(t_token *tmp, char **array, int *i, int j)
{
	int	k;
	int	l;

	j = 0;
	l = *i;
	while (tmp->content[j] != '\0')
	{
		k = 0;
		array[l] = malloc(sizeof(char)
				* ft_check_for_malloc(tmp->content, j) + 1);
		if (!array[l])
			return (ft_free_array(array));
		while (tmp->content[j] && tmp->content[j] != ' ')
		{
			array[l][k] = tmp->content[j];
			j++;
			k++;
		}
		array[l][k] = '\0';
		while (tmp->content[j] && tmp->content[j] == ' ')
			j++;
		l++;
	}
	*i = l;
	return (array);
}

char	**ft_aux_array_else(t_token *tmp, char **array, int *i)
{
	int	j;

	j = *i;
	array[j] = ft_strdup(tmp->content);
	if (!array[j])
		return (ft_free_array(array));
	j++;
	*i = j;
	return (array);
}

char	**ft_aux_array(t_token *tmp, char **array, int i)
{
	while (tmp)
	{
		if (tmp->type != SPACES)
		{
			if (!tmp->content)
				break ;
			else
			{
				if (tmp->expanded == 1 && tmp->type == STRING && tmp->content)
				{
					array = ft_aux_array_if(tmp, array, &i, 0);
				}
				else
				{
					array = ft_aux_array_else(tmp, array, &i);
				}
			}
		}
		tmp = tmp->next;
	}
	return (array);
}

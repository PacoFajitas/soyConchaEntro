/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 01:16:13 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/20 14:12:19 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_lstsize(t_token *lst)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	*ft_get_cmd_path(t_env **env, char *cmd)
{
	char	*path;
	char	**paths;
	int		i;

	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	path = ft_get_env_value(env, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoinfree(path, cmd);
		if (access(path, F_OK) == 0)
		{
			ft_free_array(paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_array(paths);
	return (NULL);
}

int	ft_count_spaces(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str || !str[i])
		return (0);
	while (str[i])
	{
		if (str[i] && str[i] == ' ')
		{
			while (str[i] && str[i] == ' ')
				i++;
			count++;
		}
		if(str[i])
			i++;
	}
	return (count);
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
	array = ft_calloc((i + 1), sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	if (cmds && cmds[0])
	{
		while (cmds[i])
		{
			array[i] = ft_strdup(cmds[i]);
			if (!array[i])
			{
				ft_free_array(cmds);
				return (ft_free_array(array));
			}
			i++;
		}
		ft_free_array(cmds);
	}
	tmp = *token;
	return (ft_aux_array(tmp, array, i));
}

int	ft_check_for_malloc(char *str, int j)
{
	int	i;

	i = 0;
	while (str[j] && str[j] != ' ')
	{
		i++;
		j++;
	}
	return (i);
}

char	**ft_aux_array(t_token *tmp, char **array, int i)
{
	int	j;
	int	k;
	
	while (tmp)
	{
		if (tmp->type != SPACES)
		{
			if (!tmp->content)
				break ;
			else
			{
				if(tmp->expanded == 1 && tmp->type == STRING && tmp->content)
				{
					j = 0;
					while (tmp->content[j] != '\0')
					{
						k = 0;
						array[i] = malloc(sizeof(char) * ft_check_for_malloc(tmp->content, j) + 1);
						if (!array[i])
							return (ft_free_array(array));
						while (tmp->content[j] && tmp->content[j] != ' ')
						{
							array[i][k] = tmp->content[j];
							j++;
							k++;
						}
						array[i][k] = '\0';
						while (tmp->content[j] && tmp->content[j] == ' ')
							j++;
						i++;
					}
				}
				else
				{
					array[i] = ft_strdup(tmp->content);
					if (!array[i])
						return (ft_free_array(array));
					i++;
				}
			}
		}
		tmp = tmp->next;
	}
	return (array);
}

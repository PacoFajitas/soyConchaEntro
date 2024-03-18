/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 01:16:13 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/18 16:19:50 by tfiguero         ###   ########.fr       */
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
		i++;
		tmp = tmp->next;
	}
	array = malloc(sizeof(char *) * (i + 1));
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
				array[i] = ft_strdup(tmp->content);
				if (!array[i])
					return (ft_free_array(array));
			}
			i++;
		}
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}

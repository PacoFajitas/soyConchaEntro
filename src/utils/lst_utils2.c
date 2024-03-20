/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlopez-i <mlopez-i@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:06:02 by mlopez-i          #+#    #+#             */
/*   Updated: 2024/03/20 20:07:10 by mlopez-i         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (str[i])
			i++;
	}
	return (count);
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

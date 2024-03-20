/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlopez-i <mlopez-i@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:27:04 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/20 21:38:45 by mlopez-i         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*ft_new_node(char *key)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (ft_memdel(key));
	new->key = key;
	new->value = ft_strdup(getenv(key));
	if (!new->value)
		return (ft_memdel(new));
	new->next = NULL;
	return (new);
}

void	ft_add_env(t_env **env, t_env *new)
{
	t_env	*temp;

	if (!*env)
	{
		*env = new;
		return ;
	}
	temp = *env;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	ft_sort_env(t_env **env)
{
	t_env	*temp;
	t_env	*temp2;
	char	*key;
	char	*value;

	temp = *env;
	while (temp)
	{
		temp2 = temp->next;
		while (temp2)
		{
			if (ft_strcmp(temp->key, temp2->key) > 0)
			{
				key = temp->key;
				value = temp->value;
				temp->key = temp2->key;
				temp->value = temp2->value;
				temp2->key = key;
				temp2->value = value;
			}
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
}

char	**ft_env_to_array(t_env **env)
{
	t_env	*temp;
	char	**envp;
	int		i;

	temp = *env;
	envp = malloc(sizeof(char *) * (ft_count_env(temp)+ 1));
	if (!envp)
		return (NULL);
	i = 0;
	temp = *env;
	while (temp)
	{
		envp[i] = ft_strjoin(temp->key, "=");
		if (!envp[i])
			return (ft_free_array(envp));
		envp[i] = ft_strjoin(envp[i], temp->value);
		if (!envp[i])
			return (ft_free_array(envp));
		i++;
		temp = temp->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	ft_change_env_value(char *key, char *value, t_env **env)
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			if (temp && temp->value)
				free(temp->value);
			temp->value = ft_strdup(value);
			return ;
		}
		temp = temp->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:44:51 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/16 21:18:26 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*ft_init_new_export(t_env **env)
{
	t_env	*env_node;

	env_node = malloc(sizeof(t_env));
	if (!env_node)
		return (NULL);
	env_node->key = ft_strdup("OLDPWD");
	if (!env_node->key)
		return (NULL);
	env_node->value = ft_strdup("");
	if (!env_node->value)
		return (NULL);
	env_node->next = *env;
	*env = env_node;
	return (*env);
}

char	*ft_get_env_value(t_env **env, char *key)
{
	t_env	*env_node;

	env_node = *env;
	while (env_node)
	{
		if (ft_strcmp(key, env_node->key) == 0)
			return (env_node->value);
		env_node = env_node->next;
	}
	return (NULL);
}

void	ft_add_export(char *str, t_env **env)
{
	t_env	*env_node;
	char	*key;
	char	*value;

	env_node = malloc(sizeof(t_env));
	key = ft_substr(str, 0, ft_strlen(str) - ft_strlen(ft_strchr(str, '=')));
	if (!key)
		return /*(ft_malloc_errror())*/;
	value = ft_strdup(ft_strchr(str, '=') + 1);
	if (!value)
	{
		free(key);
		return /*(ft_malloc_errror())*/;
	}
	env_node->key = key;
	env_node->value = value;
	env_node->next = *env;
	*env = env_node;
}

int	ft_check_equal(char	*str)
{
	size_t	i;
	size_t	cont;
	
	i = 0;
	cont = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		cont++;
		i++;
	}
	i = 0;
	while (i < cont && str[i])
	{
		if (str[i] != '_' && !ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// void	ft_export_error(char *str)
// {
// 	ft_putstr_fd("minishell: export: `", 2);
// 	ft_putstr_fd(str, 2);
// 	ft_putstr_fd("': not a valid identifier\n", 2);
// }

t_env	*ft_search_keys(char *key, t_env **list)
{
	t_env	*lista;

	lista = *list;
	while (lista)
	{
		if (ft_strcmp(key, lista->key) == 0)
		{
			if (lista->value)
				free(lista->value);
			return (lista);
		}
		lista = lista->next;
	}
	return (NULL);
}
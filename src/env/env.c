/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:26:44 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/22 10:56:51 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*Cuando el malloc falla devolvemos 0*/
int	ft_get_env(char **envp, t_env **env)
{
	int		i;
	char	*key;
	t_env	*temp;

	i = 0;
	temp = *env;
	while (envp[i])
	{
		key = ft_substr(envp[i], 0, ft_strlen(envp[i])
				- ft_strlen(ft_strchr(envp[i], '=')));
		if (!key)
			return (0);
		temp = ft_new_node(key);
		if (!temp)
			return (0);
		ft_add_env(env, temp);
		i++;
	}
	return (1);
}

void	ft_init_new_env(t_env **env)
{
	t_env	*temp;
	t_env	*temp2;

	temp = malloc(sizeof(t_env));
	temp2 = malloc(sizeof(t_env));
	if (!temp)
		return ;
	temp->key = ft_strdup("SHLVL");
	temp->value = ft_strdup("0");
	temp2->key = ft_strdup("PWD");
	temp2->value = getcwd(NULL, 0);
	temp->next = temp2;
	temp2->next = NULL;
	*env = temp;
}

void	ft_shlvl(t_env **env, t_env *temp, int shlvl, char *str)
{
	temp = *env;
	while (temp)
	{
		if (ft_strncmp(temp->key, "SHLVL", 5) == 0)
		{
			shlvl = ft_atoi(temp->value);
			if (shlvl > 999)
			{
				str = ft_itoa(shlvl + 1);
				ft_putstr_fd("minishell: warning: shell level (", 2);
				ft_putstr_fd(str, 2);
				ft_putstr_fd(") too high, resetting to 1\n", 2);
				shlvl = 0;
				free(str);
			}
			if (shlvl < 0)
				shlvl = -1;
			shlvl++;
			free(temp->value);
			temp->value = ft_itoa(shlvl);
			break ;
		}
		temp = temp->next;
	}
}

int	ft_print_env(t_env **env, t_pipe *p)
{
	t_env	*temp;
	int		out;

	out = p->out;
	if (p->out < 0)
		out = 1;
	temp = *env;
	ft_sort_env(&temp);
	while (temp)
	{
		ft_putstr_fd(temp->key, out);
		ft_putstr_fd("=", out);
		ft_putstr_fd(temp->value, out);
		ft_putstr_fd("\n", out);
		temp = temp->next;
	}
	return (1);
}

void	ft_free_env(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = tmp;
	}
}

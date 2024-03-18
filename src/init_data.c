/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:27:04 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/17 06:12:31 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_init_envs(t_env **env, t_env **export, char **envp)
{
	if (envp[0] == NULL)
	{
		ft_init_new_env(env);
		ft_init_new_export(export);
		if (!*env)
			return (0);
	}
	else
	{
		ft_get_env(envp, export);
		ft_get_env(envp, env);
	}
	ft_shlvl(env);
	ft_general_handler(0);
	ft_sort_env(env);
	return (1);
}

int	ft_init_data(t_data *data, char **envp)
{
	data->line = NULL;
	data->pipes = 0;
	data->exp = 0;
	data->token = NULL;
	data->env = NULL;
	data->export = NULL;
	data->fds = NULL;
	data->p = NULL;
	data->error = -3;
	data->fd[0] = -3;
	data->fd[1] = -3;
	data->exit = 0;
	data->off = 0;
	data->exp = 0;
	return (ft_init_envs(&data->env, &data->export, envp));
}

void	ft_clean_data(t_data *data)
{
	data->pipes = 0;
	data->exp = 0;
	if (data->token)
		ft_free_token(&data->token);
	data->token = NULL;
	if (data->line)
		data->line = ft_memdel(data->line);
	if (data->p)
		ft_free_pipe(&data->p);
	if (data->fds)
		ft_free_fds(&data->fds);
	data->p = NULL;
}

void	ft_clean_all_data(t_data *data)
{
	if (data->token)
		ft_free_token(&data->token);
	if (data->env)
		ft_free_env(&data->env);
	if (data->export)
		ft_free_env(&data->export);
	if (data->p)
		ft_free_pipe(&data->p);
	if (data->fds)
		ft_free_fds(&data->fds);
	if (data->line)
		free(data->line);
}

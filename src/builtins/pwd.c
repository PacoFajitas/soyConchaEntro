/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:35:59 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/16 23:49:30 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_pwd(t_pipe *p, t_data *data)
{
	char	*pwd;
	int		out;

	out = p->out;
	if (p->out < 0)
		out = 1;
	// pwd = ft_strdup(ft_get_env_value(env, "PWD"));
	// if (!pwd)
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		pwd = ft_strdup(ft_get_env_value(&data->env, "PWD"));
	}
	ft_putstr_fd(pwd, out);
	ft_putstr_fd("\n", out);
	free (pwd);
}

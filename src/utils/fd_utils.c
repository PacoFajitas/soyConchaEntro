/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlopez-i <mlopez-i@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:32:59 by mlopez-i          #+#    #+#             */
/*   Updated: 2024/03/23 14:22:31 by mlopez-i         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_fd(t_fd *fd, int t, int fdt, char *key)
{
	fd->fd = fdt;
	fd->not_hd = 0;
	fd->next = NULL;
	fd->type = t;
	if (key)
	{
		fd->str = ft_strdup(key);
		if (!fd->str)
			ft_error(NULL, NULL, NULL, "malloc error");
	}
}

void	ft_add_fd(t_fd **fd, t_fd *new)
{
	t_fd	*tmp;

	if (!(*fd))
	{
		*fd = new;
		return ;
	}
	tmp = *fd;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

char	*ft_expand_hd(char *str, t_env **env, int i)
{
	char	*cont;
	char	*key;

	if (!str)
		return (NULL);
	cont = NULL;
	if (str[0] == '$' && !str[1])
		return (ft_strdup("$"));
	if (ft_dollar_last(str))
		return (ft_strdup(str));
	while (str[i] && str[i] != '$')
		i++;
	cont = ft_substr(str, 0, i);
	if (!str[i])
		return (cont);
	key = ft_strdup("");
	while (str[++i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
		key = ft_strjoin_char(key, str[i]);
	cont = ft_strjoinfree(cont, ft_get_env_value(env, key));
	i -= 1;
	while (str[i++])
		cont = ft_strjoin_char(cont, str[i]);
	free(key);
	return (cont);
}

void	ft_save_hd(char *key, t_env **env, int hd[2])
{
	char	*str;
	char	*exp;

	do_sigign(SIGQUIT);
	str = readline("> ");
	while (1)
	{
		if (!str)
			exit (0);
		else if (!ft_strcmp(str, key))
			break ;
		exp = ft_expand_hd(str, env, 0);
		ft_putstr_fd(exp, hd[1]);
		ft_putstr_fd("\n", hd[1]);
		str = ft_memdel(str);
		exp = ft_memdel(exp);
		do_sigign(SIGQUIT);
		str = readline("> ");
	}
	str = ft_memdel(str);
	exp = ft_memdel(exp);
	close(hd[1]);
	close(hd[0]);
	exit (0);
}

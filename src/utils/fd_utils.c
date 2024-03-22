/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:32:59 by mlopez-i          #+#    #+#             */
/*   Updated: 2024/03/22 19:39:22 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_fd(t_fd *fd, int t, int fdt)
{
	fd->fd = fdt;
	fd->next = NULL;
	fd->type = t;
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

int	ft_save_hd(char *key, t_env **env)
{
	int		hd[2];
	char	*str;
	char	*exp;

	if (pipe(hd) == -1)
		return (0);
	init_signals(2);
	do_sigign(SIGQUIT);
	while (1)
	{
		str = readline("> ");
		if (!str)
			return (0);
		else if (!ft_strcmp(str, key))
			break ;
		exp = ft_expand_hd(str, env, 0);
		write(hd[1], exp, ft_strlen(exp));
		write(hd[1], "\n", 1);
		str = ft_memdel(str);
		exp = ft_memdel(exp);
		// do_sigign(SIGQUIT);
	}
	printf("tu puta madre");
	str = ft_memdel(str);
	exp = ft_memdel(exp);
	close(hd[1]);
	return (hd[0]);
}

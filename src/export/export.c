/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:39:10 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/17 16:18:13 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Si se hace export con una variable que ya existe, se actualiza su valor
//Si se hace export con una variable que no existe, se crea
//Si se hace export con una variable que no tiene valor, se crea con valor NULL
//Si se hace export con una variable que no tiene valor pero tiene un igual 
//el valor de ese content sera ""
//Si se hace un export += a una variable existente se le añade el valor al final
//Si se hace un export += a una variable que no existe se crea con el valor

void	ft_filter_export(t_env **env, t_env **export, char *str)
{
	t_env	*temp;
	t_env	*temp2;
	char	*key;

	if (ft_strchr(str, '='))
	{
		key = ft_substr(str, 0, ft_strlen(str) - ft_strlen(ft_strchr(str, '=')));
		temp = ft_search_keys(key, export);
		temp2 = ft_search_keys(key, env);
		free(key);
		if (temp && temp2)
		{
			temp->value = ft_strdup(ft_strchr(str, '=') + 1);
			temp2->value = ft_strdup(ft_strchr(str, '=') + 1);
		}
		else if(temp && !temp2)
		{
			ft_add_export(str, env);
			temp->value = ft_strdup(ft_strchr(str, '=') + 1);
		}
		else
		{
			ft_add_export(str, export);
			ft_add_export(str, env);
		}
	}
	else
	{
		temp = ft_search_keys(str, export);
		if(!temp)
		{
			temp = malloc(sizeof(t_env));
			temp->key = ft_strdup(str);
			temp->value = NULL;
			temp->next = NULL;
			ft_add_env(export, temp);
		}
		else
			temp->value = NULL;
	}
}

int	ft_export(t_data **data, t_pipe *p)
{
	int		i;
	int		out;

	out = p->out;
	(*data)->exit = 0;
	if(p->out == -3)
		out = 1;
	i = 1;
	if (!p->cmds[1])
	{
		ft_print_export(*data, out);
		return (1);
	}
	while (p->cmds[i])
	{
		if (p->cmds[i][0] == '=' || !ft_isalpha(p->cmds[i][0]))
			(*data)->exit = ft_error("export", "1", p->cmds[i], "not a valid identifier");
		else if (!ft_check_equal(p->cmds[i]))
			(*data)->exit = ft_error("export", "1", p->cmds[i], "not a valid identifier");
		else
			ft_filter_export(&(*data)->env, &(*data)->export, p->cmds[i]);
		i++;	
	}
	return ((*data)->exit);
}

void	ft_print_export(t_data *data, int fd)
{
	t_env	*temp;

	temp = data->export;
	while (temp)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(temp->key, fd);
		if (temp->value)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(temp->value, fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putstr_fd("\n", fd);
		temp = temp->next;
	}
}
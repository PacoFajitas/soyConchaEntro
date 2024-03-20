/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlopez-i <mlopez-i@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:39:10 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/20 19:36:14 by mlopez-i         ###   ########.fr       */
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

void	ft_filter_export2(t_data **data, char *str, t_env *temp, t_env *temp2)
{
	if (temp && temp2)
	{
		temp->value = ft_strdup(ft_strchr(str, '=') + 1);
		temp2->value = ft_strdup(ft_strchr(str, '=') + 1);
	}
	else if (temp && !temp2)
	{
		ft_add_export(str, &(*data)->env);
		temp->value = ft_strdup(ft_strchr(str, '=') + 1);
	}
	else
	{
		ft_add_export(str, &(*data)->export);
		ft_add_export(str, &(*data)->env);
	}
}

void	ft_filter_export(t_data **data, char *str, char *key, t_env *temp2)
{
	t_env	*temp;

	if (ft_strchr(str, '='))
	{
		key = ft_substr(str, 0, ft_strlen(str)
				- ft_strlen(ft_strchr(str, '=')));
		temp = ft_search_keys(key, &(*data)->export);
		temp2 = ft_search_keys(key, &(*data)->env);
		free(key);
		ft_filter_export2(data, str, temp, temp2);
	}
	else
	{
		temp = ft_search_keys(str, &(*data)->export);
		if (!temp)
		{
			temp = malloc(sizeof(t_env));
			temp->key = ft_strdup(str);
			temp->value = NULL;
			temp->next = NULL;
			ft_add_env(&(*data)->export, temp);
		}
		else
			temp->value = NULL;
	}
}

int	ft_export(t_data **data, t_pipe *p, int i)
{
	int		out;

	out = p->out;
	(*data)->exit = 0;
	if (p->out == -3)
		out = 1;
	if (!p->cmds[1])
	{
		ft_print_export(*data, out);
		return (1);
	}
	while (p->cmds[i])
	{
		if (p->cmds[i][0] == '=' || !ft_isalpha(p->cmds[i][0]))
			(*data)->exit = ft_error("export", "1", p->cmds[i],
					"not a valid identifier");
		else if (!ft_check_equal(p->cmds[i]))
			(*data)->exit = ft_error("export", "1", p->cmds[i],
					"not a valid identifier");
		else
			ft_filter_export(data, p->cmds[i], NULL, NULL);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 06:51:37 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/17 07:48:43 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*	es keyword haya espacio o no!!	*/
/*	desde el syntax checker pasarle la keyword!	*/
int	ft_heredoc(t_data *data, char *key)
{
	t_fd	*new;

	new = malloc(sizeof(t_fd));
	if (!new)
		return (0);
	new->type = HDOC;
	new->next = NULL;
	new->str = ft_strdup(key);
	if (!new->str)
		return (0);
	new->fd = ft_save_hd(key, &data->env);
	ft_add_fd(&data->fds, new);
	return (1);
}

void	ft_free_fds(t_fd **fd)
{
	t_fd	*tmp;

	while (*fd)
	{
		tmp = (*fd)->next;
		if ((*fd)->str)
			free((*fd)->str);
		free(*fd);
		*fd = tmp;
	}
}

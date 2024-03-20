/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:10:00 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/20 12:54:30 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	*ft_memdel(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

char	**ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] && *array[i])
	{
		free(array[i]);
		i++;
	}
	if (array)
		free(array);
	return (NULL);
}

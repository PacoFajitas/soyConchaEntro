/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:16:41 by tfiguero          #+#    #+#             */
/*   Updated: 2023/05/12 14:09:46 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *x, int y, size_t n )
{
	unsigned char	*i;
	size_t			j;

	i = (unsigned char *)x;
	j = 0;
	while (j < n)
	{
		if (i[j] == (unsigned char)y)
			return ((void *)&i[j]);
		j++;
	}
	return (NULL);
}

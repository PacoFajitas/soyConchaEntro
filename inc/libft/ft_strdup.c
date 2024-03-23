/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlopez-i <mlopez-i@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 23:12:47 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/23 15:58:08 by mlopez-i         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*ret;
	int		x;

	ret = malloc(ft_strlen(src) + 1);
	if (ret == NULL)
		return (NULL);
	x = 0;
	while (src && src[x])
	{
		ret [x] = src[x];
		x++;
	}
	ret[x] = '\0';
	return (ret);
}

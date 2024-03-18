/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 21:06:37 by tfiguero          #+#    #+#             */
/*   Updated: 2023/05/12 05:08:57 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

size_t	ft_strlcat(char	*dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	ret;
	size_t	dst_len;
	char	*s;

	s = (char *)src;
	i = 0;
	dst_len = ft_strlen((const char *)dst);
	if (dst_len > dstsize)
	{
		ret = ft_strlen((const char *)s) + dstsize;
	}
	else
	{
		ret = ft_strlen((const char *)s) + dst_len;
	}
	while (s[i] && dst_len + 1 < dstsize)
	{
		dst[dst_len] = s[i];
		i++;
		dst_len++;
	}
	dst[dst_len] = '\0';
	return (ret);
}

/* int	main(void)
{
	char x[50] = "Hola wena tarde wena teta por sierto";
	char y[50] = "jiji";
	
	ft_strlcat(x, y, 4);
	printf("Maquinote: %s\n", x);
	char i[50] = "Hola wena tarde wena teta por sierto";
	char j[50] = "jiji"; 
	strlcat(i, j, 40);
	printf("Machina: %s", i);
	return(0);
} */
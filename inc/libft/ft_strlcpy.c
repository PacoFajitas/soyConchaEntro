/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:31:12 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/17 05:05:47 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (i < dstsize - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

/* int	main(void)
{
	char x[50] = "Hola wena tarde wena teta por sierto";
	char y[50] = "jiji";
	
	ft_strlcpy(x, y, 4);
	printf("Maquinote: %s\n", x);
	char i[50] = "Hola wena tarde wena teta por sierto";
	char j[50] = "jiji"; 
	strlcpy(i, j, 4);
	printf("Machina: %s", i);
	return(0);
}  */
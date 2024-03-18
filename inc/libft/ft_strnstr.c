/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:36:56 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/17 05:05:39 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	need_len;

	i = 0;
	need_len = ft_strlen(needle);
	if (needle == NULL || need_len == 0)
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		while (needle[j] != '\0' && haystack[i + j] != '\0'
			&& haystack [i + j] == needle [j] && i + j < len)
		{
			j++;
		}
		if (needle[j] == '\0')
		{
			return ((char *)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}

/* int	main(void)
{
	char x[50] = "Hola wena tarde wena teta por sierto"; 
	char y[50] = " "; 
	printf("Maquinote: %s\n", ft_strnstr(x, y, (size_t)10)); 
	char i[50] = "Hola wena tarde wena teta por sierto";
	char j[50] = " "; 
	printf("Machina: %s", strnstr(i, j, (size_t)10));
	return(0);
}   */
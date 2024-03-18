/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:06:46 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/17 05:12:08 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

void	*ft_memmove(void *dst, const void*src, size_t len)
{
	int	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst > src)
	{
		i = (int)len - 1;
		while (i >= 0)
		{
			((unsigned char *) dst)[i] = ((unsigned char *) src)[i];
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < (int)len)
		{
			((unsigned char *) dst)[i] = ((unsigned char *) src)[i];
			i++;
		}
	}
	return (dst);
}
/* int main(void)
{
	int b = 50;
	char str[400] = "holaquetalestamos";
	memmove(str+2, str, b);
	printf("%s\n", str);
	char str1[400] = "holaquetalestamos";
	ft_memmove(str1+2 , str1, b);
	printf("%s\n", str1);
	char str3[200] = "holaquetalestamos";
	memmove(str3, str3+3, b);
	printf("%s\n", str3);
	char str4[200] = "holaquetalestamos";
	ft_memmove(str4 , str4+3, b);
	printf("%s\n", str4);
	return (0);
}   */
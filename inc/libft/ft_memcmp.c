/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:32:56 by tfiguero          #+#    #+#             */
/*   Updated: 2023/05/12 04:41:37 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	if (!s1 && !s2)
		return (0);
	while (i < n && (ptr1[i] == ptr2[i]))
		i++;
	if (i == n)
		return (0);
	return (ptr1[i] - ptr2[i]);
}

/* int main(void)
{
	 int b = 50;
	 char str[400] = "holaquetalestamos";
	 char str4[200] = "holaqetalestamos";
	 char str1[400] = "holaquetalestamos";
	
	ft_memcmp("teste", "teste", 6)

	 printf("R: %i\n", memcmp(str, str, b));
	 printf("T: %i\n", memcmp(str, str, b));
	
	 printf("R: %i\n", ft_memcmp(str4 , str, b));
	 printf("T: %i\n", ft_memcmp(str4 , str, b));
	 char str3[200] = "";
	
	 printf("R: %i\n", memcmp(str3, str1, b));
	 printf("T: %i\n", memcmp(str3, str1, b));
	
	 printf("R: %i\n", ft_memcmp(str4 , str3, b));
	 printf("T: %i\n", ft_memcmp(str4 , str3, b));
	 return (0);
}  */
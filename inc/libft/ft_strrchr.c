/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:56:52 by tfiguero          #+#    #+#             */
/*   Updated: 2023/05/13 16:07:17 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

char	*ft_strrchr(const char *str, int c)
{
	int	x;
	int	i;

	i = -1;
	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] == (unsigned char)c)
			i = x;
		x++;
	}
	if (i != -1)
	{
		return (&((char *)str)[i]);
	}
	if ((unsigned char)c == '\0')
	{
		return ((char *)(str + x));
	}
	return (NULL);
}
/* int	main()
{
	char str[400] = "";
	printf("T: %s\n", ft_strrchr(str, '\0'));
	printf("M: %s\n", strrchr(str, '\0'));
	printf("T: %s\n", ft_strrchr(str, 'u'));
	printf("M: %s\n", strrchr(str, 'u'));
	return (0);
}  */
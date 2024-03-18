/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:09:40 by tfiguero          #+#    #+#             */
/*   Updated: 2023/05/12 04:35:48 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_atoi(const char	*str)
{
	int	ret;
	int	sign;

	sign = 1;
	ret = 0;
	while (*str == 9 || *str == 10 || *str == 11
		|| *str == 12 || *str == 13 || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
		{
			sign = -sign;
		}
		str ++;
	}
	while (*str >= '0' && *str <= '9')
	{
		ret = (ret * 10) + *str - 48;
		str ++;
	}
	return (ret * sign);
}

/* int	main(void)
{
	printf("Maquinote: %i\n", ft_atoi("\n	9017a"));
	printf("Roboto; %i", atoi("\n	-9017a"));
}  */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:06:40 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/17 05:04:19 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_tolower(char *x)
{
	int	i;

	i = 0;
	while (x[i])
	{
		if (x[i] >= 65 && x[i] <= 90)
			x[i] = x[i] + 32;
		i++;
	}
	return (x);
}

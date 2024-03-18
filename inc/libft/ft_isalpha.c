/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:56:04 by tfiguero          #+#    #+#             */
/*   Updated: 2023/05/08 22:01:02 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_isalpha(int in)
{
	int	ret;

	ret = 0;
	if ((in >= 'A' && in <= 'Z') || (in >= 'a' && in <= 'z'))
	{
		ret = 1;
	}
	return (ret);
}
/*int	main()
{
	int i;

    i = 'a';
    while (i <= 'z')
    {
        printf("%i ",ft_isalpha(i));
        i++;
    }
}*/
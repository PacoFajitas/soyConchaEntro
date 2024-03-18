/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:34:31 by tfiguero          #+#    #+#             */
/*   Updated: 2023/05/12 04:36:47 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

/* int	main()
{
	char x[50] = "Hola wena tarde";
	char *j;

	j = &x[4];
	printf("%s\n", x);
	ft_bzero(j, (1));
	printf("%s", x);
	return(0);
} */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:15:34 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/17 05:11:53 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_countwords(char *s1, char del)
{
	int		i;
	int		j;
	char	*x;

	x = s1;
	i = 0;
	j = 0;
	while (*x)
	{
		if (*x != del && j == 0)
		{
			i++;
			j = 1;
		}
		if (*x == del)
			j = 0;
		x++;
	}
	return (i);
}

char	**ft_free_all(char **x, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(x[i]);
		i++;
	}
	free(x);
	return (NULL);
}

char	**ft_actual_split(char const *s, char c, char **ret, int j)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s != c && *s)
		{
			i++;
			s++;
		}
		if (i != 0)
		{
			ret[j] = ft_substr(s - i, 0, i);
			if (!ret[j])
				return (ft_free_all(ret, j));
			j++;
		}
		while (*s == c && *s)
			s++;
		i = 0;
	}
	ret[j] = NULL;
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		words;

	words = ft_countwords((char *)s, c);
	ret = (char **)malloc(sizeof(char **) * (words + 1));
	if (!ret)
		return (NULL);
	return (ft_actual_split(s, c, ret, 0));
}

/*  int	main(void)
{
	char *x = " hola   wena teta weno culo por sierto";


	ft_split(x, ' ');
	
}  */
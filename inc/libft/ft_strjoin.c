/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 01:43:43 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/17 05:06:50 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = (char *) malloc(s1_len + s2_len + 1);
	if (ret == NULL)
		return (NULL);
	while (i < s1_len && s1[i] != '\0')
	{
		ret[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len && s2[i] != '\0')
	{
		ret[s1_len + i] = s2[i];
		i++;
	}
	ret[s1_len + s2_len] = '\0';
	return (ret);
}

char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*ret;
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = (char *) malloc(s1_len + s2_len + 1);
	if (ret == NULL)
		return (NULL);
	while (i < s1_len && s1[i] != '\0')
	{
		ret[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len && s2[i] != '\0')
	{
		ret[s1_len + i] = s2[i];
		i++;
	}
	ret[s1_len + s2_len] = '\0';
	free(s1);
	return (ret);
}

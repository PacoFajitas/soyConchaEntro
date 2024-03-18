/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 22:54:10 by tfiguero          #+#    #+#             */
/*   Updated: 2023/05/16 16:14:38 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*temp;

	if (!lst)
		return (NULL);
	ret = malloc (sizeof(t_list));
	if (!ret)
		return (NULL);
	temp = ret;
	while (lst->next != NULL)
	{
		temp->content = f(lst->content);
		temp->next = malloc(sizeof(t_list));
		if (!temp->next)
		{
			ft_lstclear(&ret, del);
			return (NULL);
		}
		temp = temp->next;
		lst = lst->next;
	}
	temp->content = f(lst->content);
	temp->next = NULL;
	return (ret);
}

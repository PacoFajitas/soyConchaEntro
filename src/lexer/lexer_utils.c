/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlopez-i <mlopez-i@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:04:11 by mlopez-i          #+#    #+#             */
/*   Updated: 2024/03/20 19:41:30 by mlopez-i         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_new_token(char *content, int token, int exp)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (ft_memdel(content));
	new->content = content;
	new->type = token;
	new->prev = NULL;
	new->next = NULL;
	new->expanded = exp;
	return (new);
}

void	ft_add_token(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (!*token)
	{
		*token = new;
		return ;
	}
	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	ft_free_token(t_token **token)
{
	t_token	*tmp;

	while (*token)
	{
		tmp = (*token)->next;
		if ((*token) && (*token)->content)
			free((*token)->content);
		free(*token);
		*token = tmp;
	}
}

char	*ft_clean_line(char *line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] && line[i] == ' ')
		i++;
	j = ft_strlen(line) - 1;
	while (j >= 0 && line[j] == ' ')
		j--;
	tmp = ft_substr(line, i, j - i + 1);
	free(line);
	return (tmp);
}

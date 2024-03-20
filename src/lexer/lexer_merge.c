/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_merge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlopez-i <mlopez-i@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:09:19 by mlopez-i          #+#    #+#             */
/*   Updated: 2024/03/20 20:23:58 by mlopez-i         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_look_for_quotes(t_token **token)
{
	t_token	*temp;

	temp = NULL;
	while ((*token))
	{
		if ((*token)->type == 1 || (*token)->type == 2 || (*token)->type == 3)
		{
			temp = ft_merge_tokens(token);
		}
		if (!temp)
			break ;
		else if (!temp->next)
		{
			*token = temp;
			break ;
		}
		else
		{
			*token = temp;
			*token = (*token)->next;
			temp = *token;
		}
	}
	while ((*token) && (*token)->prev)
		*token = (*token)->prev;
}

void	ft_assign(t_token **token, t_token *new, t_token *temp, t_token *start)
{
	new->prev = start->prev;
	new->next = temp;
	if (temp)
	{
		temp->prev->next = NULL;
		temp->prev = new;
	}
	if (start->prev)
		start->prev->next = new;
	else
		*token = new;
	ft_free_token(&start);
}

int	ft_dollar_last(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

//Separar en otra funcion lo de dentro del if(ft_strlen(newcont)>0)
t_token	*ft_merge_tokens(t_token **token)
{
	t_token	*temp;
	t_token	*start_trim;
	t_token	*new_token;
	char	*newcont;

	newcont = ft_strdup("");
	start_trim = *token;
	temp = *token;
	new_token = NULL;
	while (temp && (temp->type == 1 | temp->type == 2 | temp->type == 3))
	{
		if (temp->content)
			newcont = ft_strjoinfree(newcont, temp->content);
		temp = temp->next;
	}
	if (ft_strlen(newcont) > 0)
	{
		new_token = ft_new_token(newcont, (*token)->type, (*token)->expanded);
		ft_assign(token, new_token, temp, start_trim);
	}
	if (new_token && new_token->next)
		return (new_token->next);
	return (new_token);
}

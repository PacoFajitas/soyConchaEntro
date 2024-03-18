/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:04:11 by mlopez-i          #+#    #+#             */
/*   Updated: 2024/03/16 21:31:26 by tfiguero         ###   ########.fr       */
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

void	ft_print_tokens(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	// printf("NEW CONTENT BELOW\n");
	while (tmp)
	{
		if (tmp->content)
			printf("%s| expandido: %i |", tmp->content, tmp->expanded);
		if (tmp->type == 0)
			printf("TYPE: space\n");
		else if (tmp->type == 1)
			printf("TYPE: string\n");
		else if (tmp->type == 2)
			printf("TYPE: comillas simples\n");
		else if (tmp->type == 3)
			printf("TYPE: comillas dobles\n");
		else if (tmp->type == 4)
			printf("TYPE: pipe | \n");
		else if (tmp->type == 5)
			printf("TYPE: heredoc << \n");
		else if (tmp->type == 6)
			printf("TYPE: redirout >\n");
		else if (tmp->type == 7)
			printf("TYPE: append >> \n");
		else if (tmp->type == 8)
			printf("TYPE: redirin <\n");
		else if (tmp->type == 9)
			printf("TYPE: dollar $ \n");
		// if (tmp->prev)
		// 	printf("\nPREV CONTENT:%s/ \n", tmp->prev->content);
		tmp = tmp->next;
	}
	printf("\n");
}

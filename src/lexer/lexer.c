/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:30:53 by mlopez-i          #+#    #+#             */
/*   Updated: 2024/03/16 19:49:49 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_quote_token(char *line, int *i)
{
	int		j;
	char	quote;
	int		type;
	char	*content;

	j = *i;
	quote = line[j];
	type = STRINGCD;
	j++;
	if (quote == '\'')
		type = STRINGCS;
	if (!line[j])
		return (ft_new_token(ft_strdup(""), type, 0));
	while (line[j] && quote != line[j])
		j++;
	content = ft_substr(line, *i + 1, j - *i - 1);
	*i = j;
	return (ft_new_token(content, type, 0));
}

t_token	*ft_str_token(char *line, int *i)
{
	int		j;
	char	*content;

	j = *i;
	while (line[j] && line[j] != ' ' && line[j] != '\'' && line[j]
		!= '\"' && line[j] != '<' && line[j] != '>' && line[j] != '|')
		j++;
	content = ft_substr(line, *i, j - *i);
	if (!content)
		return (NULL);
	*i = j - 1;
	return (ft_new_token(content, STRING, 0));
}

t_token	*ft_meta_token(char *line, int *i, t_data *data)
{
	int	j;

	j = *i;
	if (line[j] == '<' && line [j + 1] && line[j + 1] == '<')
	{
		*i = j + 1;
		return (ft_new_token(NULL, HDOC, 0));
	}
	else if (line[j] == '>' && line [j + 1] && line[j + 1] == '>')
	{
		*i = j + 1;
		return (ft_new_token(NULL, APPEND, 0));
	}
	else if (line[j] == '>')
		return (ft_new_token(NULL, REDIROUT, 0));
	else if (line[j] == '<')
		return (ft_new_token(NULL, REDIRIN, 0));
	else if (line[j] == '|')
	{
		data->pipes++;
		return (ft_new_token(NULL, PIPE, 0));
	}
	return (NULL);
}

t_token	*ft_space_token(char *line, int *i)
{
	int		j;
	char	*content;

	j = *i;
	while (line[j] && line[j] == ' ')
		j++;
	content = malloc(2);
	if (!content)
		return (NULL);
	content[0] = ' ';
	content[1] = '\0';
	*i = j - 1;
	return (ft_new_token(content, SPACES, 0));
}

int	ft_tokenize(t_data *data, char *line)
{
	t_token	*token;
	int		i;

	i = 0;
	token = NULL;
	line = ft_clean_line(line);
	data->line = line;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == ' ')
			token = ft_space_token(line, &i);
		else if (line[i] == '\'' || line[i] == '\"')
			token = ft_quote_token(line, &i);
		else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
			token = ft_meta_token(line, &i, data);
		else
			token = ft_str_token(line, &i);
		if (!token)
			return (0);
		else
			ft_add_token(&(data->token), token);
		if (line[i])
			i++;
	}
	if (!data->token || !data->token->content)
		return (1);
	// ft_print_tokens(&data->token);
	// ft_look_for_quotes(&data->token);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 04:59:43 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/20 14:10:26 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_letter(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

char	*ft_strjoin_char(char *str, char add)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new)
		return (NULL);
	while (str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = add;
	new[i + 1] = '\0';
	free(str);
	return (new);
}

char	*ft_expand_string(char *str, t_data *data, int i, int *exp)
{
	char	*cont;
	char	*key;
	char	*test;
	char	*j;
	if (!str)
		return (NULL);
	cont = NULL;
	if (str[0] == '$' && str[1] && str[1] == '?')
	{
		j = ft_itoa(data->exit);
		return (j);
	}
	else if (str[0] == '$' && !str[1])
		return (ft_strdup("$"));
	if (ft_dollar_last(str))
		return (ft_strdup(str));
	while (str[i] && str[i] != '$')
		i++;
	cont = ft_substr(str, 0, i);
	if (!str[i])
		return (cont);
	while (str[i])
	{
		key = ft_strdup("");
		while (str[++i] && str[i] != ' ' && str[i] != '$')
			key = ft_strjoin_char(key, str[i]);
		test = ft_get_env_value(&data->env, key);
		if (test)
		{
			free(key);
			key = ft_strdup(test);
			cont = ft_strjoinfree(cont, key);
			free(key);
		}
		if (str[i] != '$')
		{
			i -= 1;
			break ;
		}
	}
	while (str[i++])
		cont = ft_strjoin_char(cont, str[i]);
	*exp = 1;
	return (cont);
}

//echo "holi $ USER" no expande (imprime dolar)
char	*ft_expand_dquoted(char *str, t_data *data, int i, int *exp)
{
	char	*cont;
	char	*key;
	char		*j;

	if (!str)
		return (NULL);
	if (ft_dollar_last(str))
		return (ft_strdup(str));
	cont = ft_strdup("");
	while (str[i])
	{
		while (str[i] && str[i] != '\0' && str[i] != '$')
			cont = ft_strjoin_char(cont, str[i++]);
		key = ft_strdup("");
		while (str[i] && str[i++] && ft_is_letter(str[i]))
			key = ft_strjoin_char(key, str[i]);
		if (key && key[0] != '\0')
		{
			cont = ft_strjoinfree(cont, ft_get_env_value(&data->env, key));
			*exp = 1;
		}
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			j = ft_itoa(data->exit);
			cont = ft_strjoinfree(cont, j);
			free(j);
		}
		else if (str[i] == '$' && !str[i + 1])
			cont = ft_strjoinfree(cont, "$");
		free(key);
	}
	return (cont);
}

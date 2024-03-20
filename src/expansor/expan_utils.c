/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlopez-i <mlopez-i@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 04:59:43 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/20 21:04:32 by mlopez-i         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_check_ex_ifs(char *str, int *i)
{
	int	j;

	j = *i;
	if (str[j] != '$')
	{
		j -= 1;
		*i = j;
		return (0);
	}
	return (1);
}

char	*ft_ex_ifs(t_data *data, char *str, char *cont, int *i)
{
	char	*key;
	char	*test;
	int		j;

	j = *i;
	while (str[j])
	{
		key = ft_strdup("");
		while (str[++j] && str[j] != ' ' && str[j] != '$')
			key = ft_strjoin_char(key, str[j]);
		test = ft_get_env_value(&data->env, key);
		if (test)
		{
			free(key);
			key = ft_strdup(test);
			cont = ft_strjoinfree(cont, key);
			free(key);
		}
		if (!ft_check_ex_ifs(str, i))
			break ;
	}
	*i = j;
	return (cont);
}

char	*ft_expand_string(char *str, t_data *data, int i, int *exp)
{
	char	*cont;
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
	cont = ft_ex_ifs(data, str, cont, &i);
	while (str[i++])
		cont = ft_strjoin_char(cont, str[i]);
	*exp = 1;
	return (cont);
}

char	*ft_exdqu_ifs(char *str, t_data *data, char *cont, int *i)
{
	char	*j;
	char	*key;
	int		k;

	k = *i;
	key = ft_strdup("");
	while (str[k] && str[k++] && ft_is_letter(str[k]))
		key = ft_strjoin_char(key, str[k]);
	if (key && key[0] != '\0')
	{
		cont = ft_strjoinfree(cont, ft_get_env_value(&data->env, key));
		data->exp = 1;
	}
	else if (str[k] == '$' && str[k + 1] == '?')
	{
		j = ft_itoa(data->exit);
		cont = ft_strjoinfree(cont, j);
		free(j);
	}
	else if (str[k] == '$' && !str[k + 1])
		cont = ft_strjoinfree(cont, "$");
	free(key);
	*i = k;
	return (cont);
}

char	*ft_expand_dquoted(char *str, t_data *data, int i)
{
	char	*cont;

	if (!str)
		return (NULL);
	if (ft_dollar_last(str))
		return (ft_strdup(str));
	cont = ft_strdup("");
	while (str[i])
	{
		while (str[i] && str[i] != '\0' && str[i] != '$')
			cont = ft_strjoin_char(cont, str[i++]);
		cont = ft_exdqu_ifs(str, data, cont, &i);
	}
	return (cont);
}

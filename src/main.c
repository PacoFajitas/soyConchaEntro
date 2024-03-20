/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlopez-i <mlopez-i@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:37:26 by mlopez-i          #+#    #+#             */
/*   Updated: 2024/03/20 21:50:43 by mlopez-i         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_minihell(t_data *data)
{
	ft_general_handler(0);
	data->line = readline("minihell😭🔥👿$ ");
	ft_general_handler(1);
	add_history(data->line);
	if (!ft_tokenize(data, data->line, NULL, 0))
		return (0);
	data->token = ft_expan(&data->token, data, 0, &data->exp);
	if (!ft_syntax_error(data, &data->token))
		return (1);
	ft_look_for_quotes(&data->token);
	if (!data->token)
		return (1);
	if (!ft_parser(data, &data->token, 1, data->fds))
		return (1);
	if (ft_executor(data, data->p))
		return (0);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		status;

	status = 1;
	(void)argc;
	(void)argv;
	ft_init_data(&data, envp);
	while (status && data.off == 0)
	{
		status = ft_minihell(&data);
		ft_clean_data(&data);
	}
	return (ft_exit(&data));
}

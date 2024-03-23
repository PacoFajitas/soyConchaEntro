/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:37:26 by mlopez-i          #+#    #+#             */
/*   Updated: 2024/03/23 17:01:06 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_banner2(void)
{
	printf("\\\\\\  \\\n   \\ \\____");
	printf("___\\ \\__\\\\ \\__\\   \\ \\__\\ \\ \\__\\\\ _\\\\ \\_______\\\n");
	printf("    \\|_______|\\|__| \\|__|    \\|__|  \\|__|\\|__|\\|_______|\n");
}

void	ft_print_banner(void)
{
	printf(" ________  ________      ___    ___      ________  ________  ____");
	printf("____   ________  ___  ___  ________\n|\\   ____\\|\\   __  \\    ");
	printf("|\\  \\  /  /|    |\\   ____\\|\\   __  \\|\\   ___  \\|\\   ____");
	printf("\\|\\  \\|\\  \\|\\   __  \\\n\\ \\  \\___|\\ \\  \\|\\  \\   \\ ");
	printf("\\  \\/  / /    \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\ \\  \\ \\ ");
	printf(" \\___|\\ \\  \\\\\\  \\ \\  \\|\\  \\\n \\ \\_____  \\ \\  \\\\");
	printf("\\  \\   \\ \\    / /      \\ \\  \\    \\ \\  \\\\\\  \\ \\  \\");
	printf("\\ \\  \\ \\  \\    \\ \\   __  \\ \\   __  \\  ___   \n  \\|____");
	printf("|\\  \\ \\  \\\\\\  \\   \\/  /  /        \\ \\  \\____\\ \\  \\");
	printf("\\\\  \\ \\  \\\\ \\  \\ \\  \\____\\ \\  \\ \\  \\ \\  \\ \\  \\");
	printf("|\\  \\\n    ____\\_\\  \\ \\_______\\__/  / /           \\ \\___");
	printf("____\\ \\_______\\ \\__\\\\ \\__\\ \\_______\\ \\__\\ \\__\\ \\__");
	printf("\\ \\__\\ \\  \\\n   |\\_________\\|_______|\\___/ /             ");
	printf("\\|_______|\\|_______|\\|__| \\|__|\\|_______|\\|__|\\|__|\\|__|");
	printf("\\|__|\\/  /|\n   \\|_________|        \\|___|/                  ");
	printf("                                                       |\\___/ /");
	printf("\n                                                               ");
	printf("                                       \\|___|/\n\n _______   ___");
	printf("_____   _________  ________  ________\n|\\  ___ \\ |\\   ___  \\|");
	printf("\\___   ___\\\\   __  \\|\\   __  \\\n\\ \\   __/|\\ \\  \\\\ \\ ");
	printf(" \\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\|\\  \\\n \\ \\  \\_|/_\\ ");
	printf("\\  \\\\ \\  \\   \\ \\  \\ \\ \\   _  _\\ \\  \\\\\\  \\\n  \\ ");
	printf("\\  \\_|\\ \\ \\  \\\\ \\  \\   \\ \\  \\ \\ \\  \\\\  \\\\ \\  ");
	ft_print_banner2();
}

int	ft_minihell(t_data *data)
{
	init_signals(1);
	do_sigign(SIGQUIT);
	data->line = readline("minihell😭🔥👿$ ");
	if (!data->line)
		return (0);
	if (ft_strcmp(data->line, "\"\"") == 0
		|| ft_strcmp(data->line, "\'\'") == 0)
		return (1);
	do_sigign(SIGINT);
	add_history(data->line);
	if (!ft_tokenize(data, data->line, NULL, 0))
		return (0);
	data->token = ft_expan(&data->token, data, 0, &data->exp);
	ft_look_for_quotes(&data->token);
	if (!ft_syntax_error(data, &data->token))
		return (1);
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
	// ft_print_banner();
	ft_init_data(&data, envp);
	while (status && data.off == 0)
	{
		status = ft_minihell(&data);
		ft_clean_data(&data);
	}
	return (ft_exit(&data));
}

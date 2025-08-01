/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:50:26 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/01 02:19:35 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool	process_command(char **env, int *exit_status)
{
	t_sys			*sys;
	char			*line;

	sys = malloc(sizeof(t_sys));
	if (!sys)
		return (true);
	sys->env = env;
	line = readline("[suicideProject]$ ");
	if (!line)
	{
		printf("\n");
		return (true);
	}
	if (*line)
		add_history(line);
	if (ft_strcmp(line, "exit") == 0)
	{
		free(line);
		return (true);
	}
	sys->tokens = tokenize(line, sys);
	sys->command = handle_line(sys, *exit_status);
	debug_print_tokens(sys->tokens);
	debug_print_segments(sys->command);
	free(line);
	free_token_list(sys->tokens);
	free_segments(sys->command);
	return (false);
}

int	main(int ac, char **av, char **env)
{
	int				exit_status;
	struct termios	orig_termios;

	(void)ac;
	(void)av;
	exit_status = 0;
	setup_signals(&orig_termios);
	while (!process_command(env, &exit_status))
		;
	reset_signals(&orig_termios);
	clear_history();
	return (exit_status);
}

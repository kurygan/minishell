/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:50:26 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/11 03:17:24 by mkettab          ###   ########.fr       */
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
	sys->garbage = NULL;  // Initialize garbage collector
	line = readline("[suicideProject]$ ");
	if (!line)
	{
		printf("\n");
		gc_carbonize(&(sys->garbage));
		free(sys);
		return (true);
	}
	if (*line)
		add_history(line);
	sys->tokens = tokenize(line, sys);
	sys->command = handle_line(sys, *exit_status);
	debug_print_tokens(sys->tokens);
	debug_print_segments(sys->command);
	exec(sys->command);
	free(line);
	gc_carbonize(&(sys->garbage));
	free(sys);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:50:26 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/13 02:29:08 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool	process_command(t_sys *sys, int *exit_status)
{
	char			*line;

	line = readline("[suicideProject]$ ");
	if (!line)
	{
		printf("\n");
		gc_carbonize(&(sys->garbage));
		return (true);
	}
	add_history(line);
	sys->tokens = tokenize(line, sys);
	sys->command = handle_line(sys, *exit_status);
	//debug_print_tokens(sys->tokens);
	//debug_print_segments(sys->command);
	exec(sys);
	gc_carbonize(&(sys->garbage));
	free(line);
	return (false);
}

int	main(int ac, char **av, char **env)
{
	int				exit_status = 0;
	struct termios	orig_termios;
	t_sys *sys;

	(void)ac;
	(void)av;
	sys = malloc(sizeof(t_sys));
	if (!sys)
		return (1);
	sys->env = env;
	sys->garbage = NULL;  // Initialize garbage collector
	setup_signals(&orig_termios);
	while (!process_command(sys, &exit_status))
		;
	free(sys);
	reset_signals(&orig_termios);
	clear_history();
	return (exit_status);
}

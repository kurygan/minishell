/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:50:26 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/13 01:39:08 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool	process_command(t_sys *sys, int *exit_status)
{
	char			*line;

	while (!sys->exit_status)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
			// gc_carbonize(&(sys->garbage));
			// return (true);
		}
		if (*line)
			add_history(line);
			// return (printf("sys->command pointer: %p\n", &(sys->command)), false);
		sys->tokens = tokenize(line, sys);
		sys->command = handle_line(sys, *exit_status);
		// debug_print_tokens(sys->tokens);
		// debug_print_segments(sys->command);
		exec(sys);
		gc_carbonize(&(sys->garbage));
		free(line);
	}
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
	process_command(sys, &exit_status);
	free(sys);
	reset_signals(&orig_termios);
	clear_history();
	return (exit_status);
}

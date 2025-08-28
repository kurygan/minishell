/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:50:26 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/28 17:54:27 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool	process_command(t_sys *sys)
{
	char			*line;

	while (1)
	{
		line = readline("[petitcoquillage]$ ");
		if (!line)
		{
			printf("exit\n");
			return (sys->exit_status);
		}
		add_history(line);
		sys->tokens = tokenize(line, sys);
		sys->command = handle_line(sys);
		//debug_print_tokens(sys->tokens);
		//debug_print_segments(sys->command);
		exec(sys);
		sys->command = NULL;
		sys->tokens = NULL;
		gc_carbonize(&(sys->garbage));
		free(line);
	}
	return (false);
}

int	main(int ac, char **av, char **env)
{
	struct termios	orig_termios;
	t_sys			*sys;

	(void)ac;
	(void)av;
	ft_memset(&orig_termios, 0, sizeof(struct termios));
	sys = malloc(sizeof(t_sys));
	if (!sys)
		return (1);
	ft_memset(sys, 0, sizeof(t_sys));
	sys->exit_status = 0;
	sys->env = env;
	sys->env_was_empty = (!env || !env[0]);
	sys->garbage = NULL;
	sys->env_gc = NULL;
	sys->env_list = init_env_list(env, sys);
	setup_signals(&orig_termios);
	process_command(sys);
	gc_carbonize(&(sys->env_gc));
	free(sys);
	reset_signals(&orig_termios);
	clear_history();
	return (sys->exit_status);
}

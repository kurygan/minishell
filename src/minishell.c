/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:50:26 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/30 14:39:40 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool	process_command(t_sys *sys)
{
	char			*line;

	while (1)
	{
		if (g_signal_received)
		{
			sys->exit_status = g_signal_received;
			g_signal_received = 0;
		}
		line = readline("[petitcoquillage]$ ");
		if (!line)
		{
			printf("exit\n");
			return (sys->exit_status);
		}
		add_history(line);
		if (check_unclosed_quotes(line))
		{
			ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
			sys->exit_status = 2;
			free(line);
			continue ;
		}
		sys->tokens = tokenize(line, sys);
		if (check_synthax_error(sys, line))
			continue ;
		sys->command = handle_line(sys);
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
	int				exit_status;

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
	exit_status = sys->exit_status;
	free(sys);
	reset_signals(&orig_termios);
	clear_history();
	return (exit_status);
}

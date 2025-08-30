/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:50:26 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/30 15:16:35 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	handle_signal_status(t_sys *sys)
{
	if (g_signal_received)
	{
		sys->exit_status = g_signal_received;
		g_signal_received = 0;
	}
}

static int	handle_unclosed_quotes(char *line, t_sys *sys)
{
	if (check_unclosed_quotes(line))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
		sys->exit_status = 2;
		free(line);
		return (1);
	}
	return (0);
}

static bool	execute_command_line(char *line, t_sys *sys)
{
	sys->tokens = tokenize(line, sys);
	if (check_synthax_error(sys, line))
		return (false);
	sys->command = handle_line(sys);
	exec(sys);
	sys->command = NULL;
	sys->tokens = NULL;
	gc_carbonize(&(sys->garbage));
	return (true);
}

static bool	process_command(t_sys *sys)
{
	char	*line;

	while (1)
	{
		handle_signal_status(sys);
		line = readline("[petitcoquillage]$ ");
		if (!line)
		{
			printf("exit\n");
			return (sys->exit_status);
		}
		add_history(line);
		if (handle_unclosed_quotes(line, sys))
			continue ;
		if (!execute_command_line(line, sys))
			continue ;
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
	sys = init_system(env);
	if (!sys)
		return (1);
	setup_signals(&orig_termios);
	process_command(sys);
	return (cleanup_and_exit(sys, &orig_termios));
}

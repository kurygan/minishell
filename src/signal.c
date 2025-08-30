/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:51:32 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 14:39:40 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal_received = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	g_signal_received = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_interactive_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_exec_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_signals(struct termios *orig_termios)
{
	struct termios	new_termios;

	tcgetattr(STDIN_FILENO, orig_termios);
	setup_interactive_signals();
	new_termios = *orig_termios;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void	reset_signals(struct termios *orig_termios)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	tcsetattr(STDIN_FILENO, TCSANOW, orig_termios);
}

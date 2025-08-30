/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:51:32 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 13:21:32 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Global variable to track signal interruption
int g_signal_received = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	g_signal_received = 130;  // Set to 130 for SIGINT
	// Let the terminal display ^C first, then newline
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_interactive_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);  // Ignore SIGQUIT in interactive shell
}

void	setup_exec_signals(void)
{
	signal(SIGINT, SIG_DFL);   // Default behavior for child processes
	signal(SIGQUIT, SIG_DFL);  // Allow ^Quit to interrupt child processes
}

void	setup_signals(struct termios *orig_termios)
{
	struct termios	new_termios;

	tcgetattr(STDIN_FILENO, orig_termios);
	setup_interactive_signals();
	new_termios = *orig_termios;
	// Keep ECHOCTL enabled to show ^C and ^Quit
	// new_termios.c_lflag &= ~ECHOCTL;  // Remove this line
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void	reset_signals(struct termios *orig_termios)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	tcsetattr(STDIN_FILENO, TCSANOW, orig_termios);
}

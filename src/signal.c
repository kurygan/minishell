/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:51:32 by emetel            #+#    #+#             */
/*   Updated: 2025/08/29 17:29:13 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(struct termios *orig_termios)
{
	struct termios	new_termios;

	tcgetattr(STDIN_FILENO, orig_termios);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	new_termios = *orig_termios;
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void	reset_signals(struct termios *orig_termios)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	tcsetattr(STDIN_FILENO, TCSANOW, orig_termios);
}

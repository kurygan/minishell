/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:50:26 by mkettab           #+#    #+#             */
/*   Updated: 2025/05/29 02:23:46 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	process_command(char **env, int *exit_status)
{
	t_cmd_segment	*command;
	t_type			*tokens;
	char			*line;

	line = readline("[petitcoquillage]$ ");
	if (!line)
	{
		printf("\n");
		return (1);
	}
	if (*line)
		add_history(line);
	if (ft_strcmp(line, "exit") == 0)
	{
		free(line);
		return (1);
	}
	tokens = tokenize(line);
	command = handle_line(line, env, *exit_status);
	debug_print_tokens(tokens);
	debug_print_segments(command);
	free(line);
	free_token_list(tokens);
	free_segments(command);
	return (0);
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

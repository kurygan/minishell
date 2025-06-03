/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:50:26 by mkettab           #+#    #+#             */
/*   Updated: 2025/06/03 21:57:49 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	process_command(char **env, int *exit_status)
{
	t_cmd_segment	*command;
	t_type			*tokens;
	char			*line;
	int				exit_status;
	t_sys			*sys;

	(void)ac;
	(void)av;
	line = NULL;
	sys = malloc(sizeof(t_sys));
	if (!sys)
		return (1);
	sys->env = env;
	exit_status = 0;
	while (1)
	{
		line = readline("[petitcoquillage]$ ");
		if (!line)
		{
			printf("\n");
			break ;
		}
		if (*line)
			add_history(line);
		if (strcmp(line, "exit") == 0)
		{
			free(line);
			break ;
		}
		command = handle_line(line, exit_status, sys);
		// TODO: exécuter `command` et mettre à jour `exit_status`
		debug_print_segments(command);
		free(line);
		free_segments(command);
		// TODO: free_segments(command);
	}
	return (exit_status);
}

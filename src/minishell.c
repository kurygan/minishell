/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:50:26 by mkettab           #+#    #+#             */
/*   Updated: 2025/05/26 18:20:19 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_cmd_segment	*command;
	char			*line;
	int				exit_status;

	(void)ac;
	(void)av;
	line = NULL;
	sys = malloc(sizeof(t_sys));
	if (!sys)
		return (1);
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
		command = handle_line(line, env, exit_status);
		// TODO: exécuter `command` et mettre à jour `exit_status`
		debug_print_segments(command);
		free(line);
		free_segments(command);
		// TODO: free_segments(command);
	}
	return (exit_status);
}

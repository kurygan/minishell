/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:50:26 by mkettab           #+#    #+#             */
/*   Updated: 2025/06/18 02:16:24 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	process_command(t_sys *sys)
{
	char			*line;
	int				exit_status;

	line = NULL;
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
		sys->cmd = handle_line(line, exit_status, sys);
		// TODO: exécuter `command` et mettre à jour `exit_status`
		debug_print_segments(sys->cmd);
		free(line);
		// TODO: free_segments(command);
	}
	return (exit_status);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_sys	*sys;
	if (!env || !*env)
		return (1);
	sys = malloc(sizeof(t_sys));
	if (!sys)
		return (1);
	ft_memset(sys, 0, sizeof(t_sys));
	sys->env = env;
	process_command(sys);
	gc_free(&sys->gc, ALL);
	free(sys);
	return (1);
}
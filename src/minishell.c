/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:50:26 by mkettab           #+#    #+#             */
/*   Updated: 2025/05/20 23:03:46 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_type	*command;
	char	*line;

	(void)ac;
	(void)av;
	line = NULL;
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
		command = handle_line(line, env);
		free(line);
	}
	return (EXIT_SUCCESS);
}

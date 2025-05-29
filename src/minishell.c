/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:50:26 by mkettab           #+#    #+#             */
/*   Updated: 2025/05/29 14:46:54 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	read_input_loop(void)
{
	char	*line;

	while (1)
	{
		line = readline("[petitcoquillage]$ ");
		if (!line)
		{
			printf("\n");
			break;
		}
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}
		free(line);
	}
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	read_input_loop();
	return EXIT_SUCCESS;
}

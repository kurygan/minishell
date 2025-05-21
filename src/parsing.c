/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:01:33 by mkettab           #+#    #+#             */
/*   Updated: 2025/05/21 23:42:07 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_type	*handle_line(char *line, char **env, )
{
	t_type	*command;
	t_type	*temp;
	
	command = gc_malloc(sizeof(t_type));
	temp = command;
	if (*line == '<')
	{
		if (line[1] == '<')
			command->token = HEREDOC;
		if (line[1] == ' ')
			command->token = IN;
		else
			command->token = ERROR;
	}
}
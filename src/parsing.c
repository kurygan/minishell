/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:01:33 by mkettab           #+#    #+#             */
/*   Updated: 2025/05/27 23:05:39 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmd_segment	*handle_line(char *line, int exit_status, t_sys *sys)
{
	t_cmd_segment	*segments;

	sys->type = tokenize(line);
	segments = convert_tokens(sys);
	free_token_list(sys->type);
	expand_variables(segments, sys->env, exit_status);
	return (segments);
}

// void	plustard(void)
// {
// 	t_type	*command;
// 	t_type	*temp;

// 	command = gc_malloc(sizeof(t_type));
// 	temp = command;
// 	if (*line == '<')
// 	{
// 		if (line[1] == '<')
// 			command->token = HEREDOC;
// 		if (line[1] == ' ')
// 			command->token = IN;
// 		else
// 			command->token = ERROR;
// 	}
// }

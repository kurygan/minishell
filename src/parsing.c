/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:01:33 by mkettab           #+#    #+#             */
/*   Updated: 2025/05/26 18:19:16 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmd_segment	*handle_line(char *line, char **env, int exit_status, )
{
	t_type			*tokens;
	t_cmd_segment	*segments;

	tokens = tokenize(line);
	segments = convert_tokens(tokens);
	free_token_list(tokens);
	expand_variables(segments, env, exit_status);
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

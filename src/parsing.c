/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:01:33 by mkettab           #+#    #+#             */
/*   Updated: 2025/05/22 02:26:58 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmd_segment	*handle_line(char *line, char **env, int exit_status)
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

// 	command = ft_calloc(1, sizeof(t_type));
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

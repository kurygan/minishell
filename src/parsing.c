/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:01:33 by mkettab           #+#    #+#             */
/*   Updated: 2025/05/29 00:26:00 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmd_segment	*handle_line(char *line, char **env, int exit_status)
{
	t_type			*tokens;
	t_cmd_segment	*segments;

	tokens = tokenize(line);
	if (!tokens)
		return (NULL);
	segments = convert_tokens(tokens);
	free_token_list(tokens);
	expand_variables(segments, env, exit_status);
	return (segments);
}

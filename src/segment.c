/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:34:58 by emetel            #+#    #+#             */
/*   Updated: 2025/08/08 01:17:57 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	handle_pipe_token(t_type *token, t_cmd_segment **current,
							t_cmd_segment **head, t_sys *sys)
{
	(void)token;
	if (*current)
	{
		(*current)->next = gc_calloc(&(sys->garbage), sizeof(t_cmd_segment));
		if ((*current)->next)
			(*current)->next->sys = sys;
	}
	if (*current)
		*current = (*current)->next;
	else
	{
		*current = gc_calloc(&(sys->garbage), sizeof(t_cmd_segment));
		if (*current)
			(*current)->sys = sys;
	}
	if (!*head)
		*head = *current;
}

static void	handle_target_token(t_type *token, t_cmd_segment **current,
							t_cmd_segment **head, t_sys *sys)
{
	if (!*current)
	{
		*current = gc_calloc(&(sys->garbage), sizeof(t_cmd_segment));
		if (*current)
			(*current)->sys = sys;
		if (!*head)
			*head = *current;
	}
	(*current)->heredoc = gc_strdup(token->str, &(sys->garbage));
}

static void	process_token(t_type *token, t_cmd_segment **current,
						t_cmd_segment **head, t_sys *sys)
{
	
	if (token->token == PIPE)
		handle_pipe_token(token, current, head, sys);
	else if (token->token == CMD || token->token == ARGS
		|| token->token == SINGLE_QUOTE || token->token == DOUBLE_QUOTE)
		handle_command_token(token, current, head, sys);
	else if (token->token == OPTIONS)
		handle_option_token(token, current, head, sys);
	else if (token->token == REDIR_IN || token->token == REDIR_OUT
		|| token->token == REDIR_APPEND || token->token == REDIR_HEREDOC)
	{
		handle_redirection_token(token, current, head, sys);
	}
	else if (token->token == REDIR_TARGET)
		handle_target_token(token, current, head, sys);
}

t_cmd_segment	*convert_tokens(t_sys *sys)
{
	t_cmd_segment	*head;
	t_cmd_segment	*current;
	t_type			*token;

	head = NULL;
	current = NULL;
	token = sys->tokens;
	while (token)
	{
		process_token(token, &current, &head, sys);
		token = token->next;
	}
	return (head);
}

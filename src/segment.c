/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:34:58 by emetel            #+#    #+#             */
/*   Updated: 2025/06/10 22:54:01 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	handle_pipe_token(t_sys *sys, t_cmd_segment **current)
{
	if (*current)
	{
		(*current)->next = init_segment(sys);
		(*current)->next->prev = *current;
		*current = (*current)->next;
	}
	else
		*current = init_segment(sys);
	if (!sys->cmd)
		sys->cmd = *current;
}

static void	handle_target_token(t_sys *sys, t_cmd_segment **current)
{
	if (!*current)
	{
		*current = init_segment(sys);
		if (!sys->cmd)
			sys->cmd = *current;
	}
	(*current)->heredoc = gc_strdup(sys->type->str, &sys->gc, OTHER);
}

static void	process_token(t_sys *sys, t_cmd_segment **current, t_type **next)
{
	if (sys->type->token == PIPE)
		handle_pipe_token(sys, current);
	else if (sys->type->token == CMD || sys->type->token == ARGS)
		handle_command_token(sys, current);
	else if (sys->type->token == OPTIONS)
		handle_option_token(sys, current);
	else if (sys->type->token == REDIR_IN || sys->type->token == REDIR_OUT
		|| sys->type->token == REDIR_APPEND || sys->type->token == REDIR_HEREDOC)
	{
		handle_redirection_token(sys, next, current);
	}
	else if (sys->type->token == REDIR_TARGET)
		handle_target_token(sys, current);
}

t_cmd_segment	*init_segment(t_sys *sys)
{
	t_cmd_segment	*seg;

	seg = gc_malloc(sizeof(t_cmd_segment), &sys->gc, OTHER);
	if (!seg)
		return (NULL);
	ft_memset(seg, 0, sizeof(t_cmd_segment));
	return (seg);
}

t_cmd_segment	*convert_tokens(t_sys *sys)
{
	t_type			*token;
	t_cmd_segment	*curr;

	curr = NULL;
	token = sys->type;
	while (token)
	{
		process_token(sys, &curr, &token);
		token = token->next;
	}
	return (sys->cmd);
}

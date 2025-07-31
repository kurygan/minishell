/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:34:58 by emetel            #+#    #+#             */
/*   Updated: 2025/07/31 21:08:00 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	handle_pipe_token(t_type *token, t_cmd_segment **current,
							t_cmd_segment **head)
{
	(void)token;
	if (*current)
		(*current)->next = init_segment();
	if (*current)
		*current = (*current)->next;
	else
		*current = init_segment();
	if (!*head)
		*head = *current;
}

static void	handle_target_token(t_type *token, t_cmd_segment **current,
							t_cmd_segment **head)
{
	if (!*current)
	{
		*current = init_segment();
		if (!*head)
			*head = *current;
	}
	(*current)->heredoc = ft_strdup(token->str);
}

static void	process_token(t_type *token, t_cmd_segment **current,
						t_cmd_segment **head, t_type **next)
{
	if (token->token == PIPE)
		handle_pipe_token(token, current, head);
	else if (token->token == CMD || token->token == ARGS)
		handle_command_token(token, current, head);
	else if (token->token == OPTIONS)
		handle_option_token(token, current, head);
	else if (token->token == REDIR_IN || token->token == REDIR_OUT
		|| token->token == REDIR_APPEND || token->token == REDIR_HEREDOC)
	{
		handle_redirection_token(token, next, current, head);
	}
	else if (token->token == REDIR_TARGET)
		handle_target_token(token, current, head);
}

t_cmd_segment	*init_segment(void)
{
	t_cmd_segment	*seg;

	seg = malloc(sizeof(t_cmd_segment));
	if (!seg)
		return (NULL);
	seg->cmd = NULL;
	seg->args = NULL;
	seg->options = NULL;
	seg->infile = NULL;
	seg->heredoc = NULL;
	seg->outfile = NULL;
	seg->append_mode = 0;
	seg->next = NULL;
	return (seg);
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
		process_token(token, &current, &head, &token);
		token = token->next;
	}
	return (head);
}

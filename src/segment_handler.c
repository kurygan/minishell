/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:56:30 by emetel            #+#    #+#             */
/*   Updated: 2025/06/23 20:51:15 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	add_arg_to_segment(t_cmd_segment *current, t_sys *sys)
{
	int		i;
	char	**new_args;
	char	*arg_str;

	i = 0;
	arg_str = sys->type->str;
	if (current->args)
	{
		while (current->args[i])
			i++;
	}
	new_args = (char **)gc_malloc(sizeof(char *) * (i + 2), &sys->gc, PARSING);
	if (!new_args)
		return ;
	i = 0;
	if (current->args)
	{
		while (current->args[i])
		{
			new_args[i] = current->args[i];
			i++;
		}
	}
	new_args[i] = gc_strdup(arg_str, &sys->gc, PARSING);
	new_args[i + 1] = NULL;
	current->args = new_args;
}

void	handle_command_token(t_sys *sys, t_cmd_segment **current)
{
	if (!*current)
	{
		*current = init_segment(sys);
		if (!sys->cmd)
			sys->cmd = *current;
	}
	if (!(*current)->cmd && sys->type->token == CMD)
		(*current)->cmd = gc_strdup(sys->type->str, &sys->gc, PARSING);
	else
		add_arg_to_segment(*current, sys);
}

void	handle_redirection_token(t_sys *sys, t_type **next,
		t_cmd_segment **current)
{
	t_type	*token;

	token = sys->type;
	if (!*current)
	{
		*current = init_segment(sys);
		if (!sys->cmd)
			sys->cmd = *current;
	}
	if ((*next)->next && (*next)->next->token != PIPE)
	{
		*next = (*next)->next;
		if (token->token == REDIR_IN)
			(*current)->infile = gc_strdup((*next)->str, &sys->gc, PARSING);
		else if (token->token == REDIR_OUT || token->token == REDIR_APPEND)
		{
			(*current)->outfile = gc_strdup((*next)->str, &sys->gc, PARSING);
			if (token->token == REDIR_APPEND)
				(*current)->append_mode = 1;
			else
				(*current)->append_mode = 0;
		}
		else if (token->token == REDIR_HEREDOC
			&& (*next)->token == REDIR_TARGET)
			(*current)->heredoc = gc_strdup((*next)->str, &sys->gc, PARSING);
	}
}

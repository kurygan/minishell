/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:56:30 by emetel            #+#    #+#             */
/*   Updated: 2025/08/17 02:26:51 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	add_arg_to_segment(t_cmd_segment *current, const char *arg_str, \
				t_sys *sys)
{
	(void)sys;
	int		i;
	char	**new_args;

	(void)sys;
	i = 0;
	if (current->args)
	{
		while (current->args[i])
			i++;
	}
	new_args = (char **)gc_malloc(&(sys->garbage), sizeof(char *) * (i + 2));
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
	new_args[i] = gc_strdup(arg_str, &(sys->garbage));
	new_args[i + 1] = NULL;
	current->args = new_args;
}

void	handle_command_token(t_type *token, t_cmd_segment **current,
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
	if (!(*current)->cmd && (token->token == CMD || token->token == SINGLE_QUOTE
			|| token->token == DOUBLE_QUOTE))
		(*current)->cmd = gc_strdup(token->str, &(sys->garbage));
	else
		add_arg_to_segment(*current, token->str, sys);
}

void	handle_redirection_token(t_type *token, t_cmd_segment **current,
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
	if (token->next && token->next->token == REDIR_TARGET)
	{
		if (token->token == REDIR_IN)
			(*current)->infile = gc_strdup(token->next->str, &(sys->garbage));
		else if (token->token == REDIR_OUT || token->token == REDIR_APPEND)
		{
			(*current)->outfile = gc_strdup(token->next->str, &(sys->garbage));
			if (token->token == REDIR_APPEND)
				(*current)->append_mode = 1;
			else
				(*current)->append_mode = 0;
		}
		else if (token->token == REDIR_HEREDOC)
			(*current)->heredoc = gc_strdup(token->next->str, &(sys->garbage));
	}
}

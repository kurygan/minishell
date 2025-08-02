/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:56:30 by emetel            #+#    #+#             */
/*   Updated: 2025/08/02 23:43:39 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	add_arg_to_segment(t_cmd_segment *current, const char *arg_str,
				t_sys *sys)
{
	(void)sys;
	int		i;
	char	**new_args;

	i = 0;
	if (current->args)
	{
		while (current->args[i])
			i++;
	}
	new_args = (char **)malloc(sizeof(char *) * (i + 2));
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
		free(current->args);
	}
	new_args[i] = ft_strdup(arg_str);
	new_args[i + 1] = NULL;
	current->args = new_args;
}

void	handle_command_token(t_type *token, t_cmd_segment **current,
						t_cmd_segment **head, t_sys *sys)
{
	if (!*current)
	{
		*current = ft_calloc(1, sizeof(t_cmd_segment));
		if (*current)
			(*current)->sys = sys;
		if (!*head)
			*head = *current;
	}
	if (!(*current)->cmd && token->token == CMD)
		(*current)->cmd = ft_strdup(token->str);
	else
		add_arg_to_segment(*current, token->str, sys);
}

void	handle_redirection_token(t_type *token, t_cmd_segment **current,
			t_cmd_segment **head, t_sys *sys)
{
	t_type **next = &token;

	if (!*current)
	{
		*current = ft_calloc(1, sizeof(t_cmd_segment));
		if (*current)
			(*current)->sys = sys;
		if (!*head)
			*head = *current;
	}
	if ((*next)->next && (*next)->next->token != PIPE)
	{
		*next = (*next)->next;
		if (token->token == REDIR_IN)
			(*current)->infile = ft_strdup((*next)->str);
		else if (token->token == REDIR_OUT || token->token == REDIR_APPEND)
		{
			(*current)->outfile = ft_strdup((*next)->str);
			if (token->token == REDIR_APPEND)
				(*current)->append_mode = 1;
			else
				(*current)->append_mode = 0;
		}
		else if (token->token == REDIR_HEREDOC
			&& (*next)->token == REDIR_TARGET)
			(*current)->heredoc = ft_strdup((*next)->str);
	}
}

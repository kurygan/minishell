/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synthax_detection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 19:42:52 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/29 21:28:51 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool double_pipe_check(t_type *token)
{
	if (token->token == PIPE)
	{
		if (token->next && token->next->token == PIPE)
		{
			ft_printf("syntax error near unexpected token `|\'\n");
			return (true);
		}
		if (!token->next)
		{
			ft_printf("syntax error near unexpected token `newline\'\n");
			return (true);
		}
	}
	return (false);
}

static bool pipe_and_redir_check(t_type *token)
{
	if (is_redirection_token(token->token))
	{
		if (!token->next)
		{
			ft_printf("syntax error near unexpected token `newline\'\n");
			return (true);
		}
		else if (token->next && token->next->token == PIPE)
		{
			ft_printf("syntax error near unexpected token `|\'\n");
			return (true);
		}
		else if (token->next && is_redirection_token(token->next->token))
		{
			ft_printf("syntax error near unexpected token `%c\'\n", *token->next->str);
			return (true);
		}
	}
	return (false);
}

bool check_synthax_error(t_sys *sys, char *line)
{
	t_type	*current = sys->tokens;
	int		is_error;

	is_error = false;
	if (!sys->tokens)
		return false;
	if (sys->tokens->token == PIPE)
	{
		ft_printf("syntax error near unexpected token `|\'\n");
		is_error = true;
	}
	while(current && !is_error)
	{
		is_error = double_pipe_check(current);
		if (!is_error)
			is_error = pipe_and_redir_check(current);
		if (!is_error && current->next)
			current = current->next;
		else
			break;
	}
	if (is_error)
	{
		sys->exit_status = 2;
		gc_carbonize(&sys->garbage);
		free(line);
		sys->command = NULL;
		sys->tokens = NULL;
	}
	return (is_error);
}

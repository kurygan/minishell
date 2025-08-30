/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synthax_detection2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:25:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 15:25:00 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	double_pipe_check(t_type *token)
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

bool	pipe_and_redir_check(t_type *token)
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
			ft_printf("syntax error near unexpected token `%c\'\n", \
				*token->next->str);
			return (true);
		}
	}
	return (false);
}

int	check_initial_pipe(t_sys *sys)
{
	if (sys->tokens->token == PIPE)
	{
		ft_printf("syntax error near unexpected token `|\'\n");
		return (1);
	}
	return (0);
}

int	check_token_syntax(t_type *current)
{
	int	is_error;

	is_error = double_pipe_check(current);
	if (!is_error)
		is_error = pipe_and_redir_check(current);
	return (is_error);
}

void	handle_syntax_error(t_sys *sys, char *line)
{
	sys->exit_status = 2;
	gc_carbonize(&sys->garbage);
	free(line);
	sys->command = NULL;
	sys->tokens = NULL;
}

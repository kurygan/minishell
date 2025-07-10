/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 00:48:46 by emetel            #+#    #+#             */
/*   Updated: 2025/06/23 21:00:55 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_token	identify_redirection_type(char *line, int *i, char **symbol)
{
	t_token	type;

	if (line[*i + 1] == line[*i])
	{
		*symbol = ft_substr(line, *i, 2);
		if (line[*i] == '<')
			type = REDIR_HEREDOC;
		else
			type = REDIR_APPEND;
		(*i) += 2;
	}
	else
	{
		*symbol = ft_substr(line, *i, 1);
		if (line[*i] == '<')
			type = REDIR_IN;
		else
			type = REDIR_OUT;
		(*i)++;
	}
	return (type);
}

static char	*extract_quoted_target(char *line, int *i, char quote)
{
	int		start;
	char	*target;

	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	target = ft_substr(line, start, *i - start);
	if (line[*i])
		(*i)++;
	return (target);
}

static char	*extract_unquoted_target(char *line, int *i)
{
	int		start;
	char	*target;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
		(*i)++;
	target = ft_substr(line, start, *i - start);
	return (target);
}

static void	handle_redirection_target(char *line, int *i, t_sys *sys,
									t_token type)
{
	char	*limiter;

	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
	if (!(line[*i] && line[*i] != '|' && line[*i] != '<' && line[*i] != '>'))
		return ;
	if (line[*i] == '\'' || line[*i] == '\"')
		limiter = extract_quoted_target(line, i, line[*i]);
	else
		limiter = extract_unquoted_target(line, i);
	if (type == REDIR_HEREDOC)
		sys->type = add_token(sys, limiter, REDIR_TARGET);
	else
		sys->type = add_token(sys, limiter, ARGS);
}

void	handle_redirection(char *line, int *i, t_sys *sys)
{
	char	*symbol;
	t_token	type;

	type = identify_redirection_type(line, i, &symbol);
	sys->type = add_token(sys, symbol, type);
	handle_redirection_target(line, i, sys, type);
}

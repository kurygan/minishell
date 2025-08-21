/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 00:48:46 by emetel            #+#    #+#             */
/*   Updated: 2025/08/18 06:33:51 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_token	identify_redirection_type(char *line, int *i, char **symbol, \
					t_sys *sys)
{
	t_token	type;

	(void)sys;
	if (line[*i + 1] == line[*i])
	{
		*symbol = gc_substr(line, *i, 2, &(sys->garbage));
		if (line[*i] == '<')
			type = REDIR_HEREDOC;
		else
			type = REDIR_APPEND;
		(*i) += 2;
	}
	else
	{
		*symbol = gc_substr(line, *i, 1, &(sys->garbage));
		if (line[*i] == '<')
			type = REDIR_IN;
		else
			type = REDIR_OUT;
		(*i)++;
	}
	return (type);
}

char	*extract_quoted_target(char *line, int *i, char quote, t_sys *sys)
{
	int		start;
	char	*target;

	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	target = gc_substr(line, start, *i - start, &(sys->garbage));
	if (line[*i])
		(*i)++;
	return (target);
}

static char	*extract_unquoted_target(char *line, int *i, t_sys *sys)
{
	int		start;
	char	*target;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
		(*i)++;
	target = gc_substr(line, start, *i - start, &(sys->garbage));
	return (target);
}

static void	handle_redirection_target(char *line, int *i, t_type **lst,
									t_token type)
{
	char	*limiter;

	(void)type;
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
	if (!(line[*i] && line[*i] != '|' && line[*i] != '<' && line[*i] != '>'))
		return ;
	if (type == REDIR_HEREDOC)
		limiter = extract_unquoted_target(line, i, (*lst)->sys);
	else if (line[*i] == '\'' || line[*i] == '\"')
		limiter = extract_quoted_target(line, i, line[*i], (*lst)->sys);
	else
		limiter = extract_unquoted_target(line, i, (*lst)->sys);
	*lst = add_token(*lst, limiter, REDIR_TARGET, (*lst)->sys);
}

void	handle_redirection(char *line, int *i, t_type **lst, t_sys *sys)
{
	char	*symbol;
	t_token	type;

	type = identify_redirection_type(line, i, &symbol, sys);
	*lst = add_token(*lst, symbol, type, sys);
	handle_redirection_target(line, i, lst, type);
}

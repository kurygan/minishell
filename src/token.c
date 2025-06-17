/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 02:42:19 by emetel            #+#    #+#             */
/*   Updated: 2025/06/04 04:49:50by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	handle_and_check_quote(char *line, int *i, t_sys *sys)
{
	int	old_i;

	old_i = *i;
	handle_quote(line, i, sys->type, line[old_i]);
	if (*i == old_i)
		return (1);
	return (0);
}

static void	assign_cmd_and_args(t_sys *sys)
{
	t_type	*tmp;
	int		expect_cmd;

	tmp = sys->type;
	expect_cmd = 1;
	while (tmp)
	{
		if (tmp->token == CMD)
		{
			if (expect_cmd)
				expect_cmd = 0;
			else
				tmp->token = ARGS;
		}
		else if (tmp->token == PIPE)
			expect_cmd = 1;
		else if (tmp->token == REDIR_IN || tmp->token == REDIR_OUT
			|| tmp->token == REDIR_APPEND || tmp->token == REDIR_HEREDOC)
		{
			if (tmp->next)
				tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}

t_type	*tokenize(char *line, t_sys *sys)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else if (line[i] == '|')
			handle_pipe(line, &i, sys);
		else if (line[i] == '<' || line[i] == '>')
			handle_redirection(line, &i, sys);
		else if (line[i] == '\'' || line[i] == '\"')
		{
			if (handle_and_check_quote(line, &i, sys))
				return (NULL);
		}
		else
			handle_word(line, &i, sys);
	}
	assign_cmd_and_args(sys);
	return (sys->type);
}

t_type	*add_token(t_sys *sys, char *str, t_token token)
{
	t_type	*new;
	t_type	*tmp;

	new = gc_calloc(sizeof(t_type), &sys->gc, type);
	if (!new)
		return (NULL);
	new->str = gc_strdup(str, &sys->gc, type);
	if (!new->str)
		return (NULL);
	new->token = token;
	if (!sys->type)
		return (new);
	tmp = sys->type;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
	new->prev = tmp;
	return (sys->type);
}

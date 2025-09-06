/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 02:42:19 by emetel            #+#    #+#             */
/*   Updated: 2025/09/06 15:02:34 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	handle_and_check_quote(char *line, int *i, t_type **lst, t_sys *sys)
{
	char	*quoted_thing;
	t_token	token_type;

	quoted_thing = extract_quoted_arg(line, i, line[*i], sys);
	if (line[*i - 1] == '\'')
		token_type = SINGLE_QUOTE;
	else
		token_type = DOUBLE_QUOTE;
	*lst = add_token((*lst), quoted_thing, token_type, sys);
	return (0);
}

static void	handle_token_assignment(t_type *tmp, int *expect_cmd)
{
	if (tmp->token == PIPE)
	{
		*expect_cmd = 1;
		return ;
	}
	if (tmp->token == CMD || tmp->token == SINGLE_QUOTE
		|| tmp->token == DOUBLE_QUOTE)
	{
		if (*expect_cmd)
			*expect_cmd = 0;
		else
			tmp->token = ARGS;
	}
}

static void	assign_cmd_and_args(t_type *token_lst, t_sys *sys)
{
	t_type	*tmp;
	int		expect_cmd;

	(void)sys;
	tmp = token_lst;
	expect_cmd = 1;
	while (tmp)
	{
		if (tmp->prev && tmp->token != PIPE && \
			!is_redirection_token(tmp->token) && tmp->token != REDIR_TARGET
			&& tmp->token != SINGLE_QUOTE && tmp->token != DOUBLE_QUOTE)
			tmp->token = CMD;
		if (tmp->token == PIPE)
		{
			expect_cmd = 1;
			tmp = tmp->next;
			continue ;
		}
		handle_token_assignment(tmp, &expect_cmd);
		tmp = tmp->next;
	}
}

static int	process_token_char(char *line, int *i, t_type **token_lst, \
	t_sys *sys)
{
	if (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	else if (line[*i] == '|')
		handle_pipe(i, token_lst, sys);
	else if (line[*i] == '<' || line[*i] == '>')
		handle_redirection(line, i, token_lst, sys);
	else if (line[*i] == '\'' || line[*i] == '\"')
	{
		if (handle_and_check_quote(line, i, token_lst, sys))
			return (1);
	}
	else
		handle_word(line, i, token_lst, sys);
	return (0);
}

t_type	*tokenize(char *line, t_sys *sys)
{
	int		i;
	t_type	*token_lst;

	i = 0;
	token_lst = NULL;
	while (line[i])
	{
		if (process_token_char(line, &i, &token_lst, sys))
			return (NULL);
	}
	assign_cmd_and_args(token_lst, sys);
	return (token_lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 02:42:19 by emetel            #+#    #+#             */
/*   Updated: 2025/08/22 20:29:20 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	handle_and_check_quote(char *line, int *i, t_type **lst, t_sys *sys)
{
	int	old_i;

	old_i = *i;
	handle_quote(line, i, lst, sys);
	if (*i == old_i)
		return (1);
	return (0);
}

static void	process_token_type(t_type *tmp, int *expect_cmd)
{
	if (tmp->token == REDIR_IN || tmp->token == REDIR_OUT
		|| tmp->token == REDIR_APPEND || tmp->token == REDIR_HEREDOC
		|| tmp->token == REDIR_TARGET || tmp->token == PIPE)
	{
		if (tmp->token == PIPE)
			*expect_cmd = 1;
		return ;
	}
	if (tmp->prev && !(tmp->prev->token == REDIR_TARGET \
		|| tmp->prev->token == REDIR_IN || tmp->prev->token == REDIR_OUT \
		|| tmp->prev->token == REDIR_APPEND \
		|| tmp->prev->token == REDIR_HEREDOC))
		tmp->token = ARGS;
	if (tmp->token == CMD || tmp->token == SINGLE_QUOTE
		|| tmp->token == DOUBLE_QUOTE)
	{
		if (*expect_cmd)
			*expect_cmd = 0;
		else
			tmp->token = ARGS;
	}
	else if (tmp->token == PIPE)
		*expect_cmd = 1;
}

static void	handle_pipe_token(t_type *tmp, int *expect_cmd)
{
	if (tmp->prev && tmp->prev->token == PIPE)
	{
		tmp->token = CMD;
		*expect_cmd = 0;
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
		handle_pipe_token(tmp, &expect_cmd);
		if (tmp->prev && tmp->prev->token == PIPE)
		{
			tmp = tmp->next;
			continue ;
		}
		process_token_type(tmp, &expect_cmd);
		tmp = tmp->next;
	}
}

t_type	*tokenize(char *line, t_sys *sys)
{
	int		i;
	t_type	*token_lst;

	i = 0;
	token_lst = NULL;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else if (line[i] == '|')
			handle_pipe(&i, &token_lst, sys);
		else if (line[i] == '<' || line[i] == '>')
			handle_redirection(line, &i, &token_lst, sys);
		else if (line[i] == '\'' || line[i] == '\"')
		{
			if (handle_and_check_quote(line, &i, &token_lst, sys))
				return (NULL);
		}
		else
			handle_word(line, &i, &token_lst, sys);
	}
	assign_cmd_and_args(token_lst, sys);
	return (token_lst);
}

t_type	*add_token(t_type *list, char *str, t_token token, t_sys *sys)
{
	t_type	*new;
	t_type	*tmp;

	new = gc_malloc(&(sys->garbage), sizeof(t_type));
	ft_memset(new, 0, sizeof(t_type));
	new->str = gc_strdup(str, &(sys->garbage));
	new->token = token;
	new->sys = sys;
	if (!list)
		return (new);
	tmp = list;
	while (1)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	tmp->next = new;
	new->prev = tmp;
	new->next = NULL;
	return (list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 02:42:19 by emetel            #+#    #+#             */
/*   Updated: 2025/05/21 02:38:25 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_type	*add_token(t_type *list, char *str, t_token token)
{
	t_type	*new;
	t_type	*tmp;

	new = ft_calloc(1, sizeof(t_type));
	new->str = ft_strdup(str);
	new->token = token;
	if (!list)
		return (new);
	tmp = list;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
	new->prev = tmp;
	return (list);
}

static void	assign_cmd_and_args(t_type *token_lst)
{
	t_type	*tmp;
	int		expect_cmd;

	tmp = token_lst;
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
		tmp = tmp->next;
	}
}

t_type	*tokenize(char *line)
{
	int		i;
	int		start;
	char	*word;
	char	*symbol;
	t_type	*token_lst;

	i = 0;
	token_lst = NULL;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
		{
			i++;
			continue ;
		}
		if (line[i] == '|')
		{
			symbol = ft_strdup("|");
			token_lst = add_token(token_lst, symbol, PIPE);
			free(symbol);
			i++;
			continue ;
		}
		if (line[i] == '<' || line[i] == '>')
		{
			if (line[i + 1] == line[i])
			{
				symbol = ft_substr(line, i, 2);
				if (line[i] == '<')
					token_lst = add_token(token_lst, symbol, HEREDOC);
				else
					token_lst = add_token(token_lst, symbol, APPEND);
				free(symbol);
				i += 2;
				continue ;
			}
			else
			{
				symbol = ft_substr(line, i, 1);
				if (line[i] == '<')
					token_lst = add_token(token_lst, symbol, IN);
				else
					token_lst = add_token(token_lst, symbol, TRUNCATE);
				free(symbol);
				i++;
				continue ;
			}
		}
		if (line[i] == '\'')
		{
			i++;
			start = i;
			while (line[i] && line[i] != '\'')
				i++;
			word = ft_substr(line, start, i - start);
			token_lst = add_token(token_lst, word, CMD);
			free(word);
			if (line[i] == '\'')
				i++;
			continue ;
		}
		if (line[i] == '\"')
		{
			i++;
			start = i;
			while (line[i] && line[i] != '\"')
				i++;
			word = ft_substr(line, start, i - start);
			token_lst = add_token(token_lst, word, CMD);
			free(word);
			if (line[i] == '\"')
				i++;
			continue ;
		}
		start = i;
		while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '|'
			&& line[i] != '<' && line[i] != '>')
			i++;
		word = ft_substr(line, start, i - start);
		token_lst = add_token(token_lst, word, CMD);
		free(word);
	}
	assign_cmd_and_args(token_lst);
	return (token_lst);
}

void	plustard(void)
{
	t_type	*command;
	t_type	*temp;

	command = ft_calloc(1, sizeof(t_type));
	temp = command;
	if (*line == '<')
	{
		if (line[1] == '<')
			command->token = HEREDOC;
		if (line[1] == ' ')
			command->token = IN;
		else
			command->token = ERROR;
	}
}

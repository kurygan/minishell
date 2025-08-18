/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:08:22 by emetel            #+#    #+#             */
/*   Updated: 2025/08/17 02:21:24 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_option(char *word)
{
	int	i;

	i = 1;
	if (!word)
		return (0);
	if (word[0] != '-')
		return (0);
	if (word[1] == '\0')
		return (0);
	while (word[i])
	{
		if (word[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	is_quoted_content(char *word)
{
	int	i;

	i = 0;
	if (!word)
		return (0);
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void	handle_pipe(char *line, int *i, t_type **lst, t_sys *sys)
{
	char	*symbol;

	(void)line;
	symbol = ft_strdup("|");
	*lst = add_token(*lst, symbol, PIPE, sys);
	(*i)++;
}

void	handle_quote(char *line, int *i, t_type **lst, t_sys *sys)
{
	int		start;
	char	*word;
	char	quote;
	t_token	token_type;

	quote = line[*i];
	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
	{
		*i = start;
		return ;
	}
	word = gc_substr(line, start, (*i - start) + 1, &(sys->garbage));
	if (quote == '\'')
		token_type = SINGLE_QUOTE;
	else
		token_type = DOUBLE_QUOTE;
	*lst = add_token(*lst, word, token_type, sys);
	(*i)++;
}

void	handle_word(char *line, int *i, t_type **lst, t_sys *sys)
{
	int		start;
	char	*word;
	t_token	token_type;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>'
		&& line[*i] != '\'' && line[*i] != '\"')
		(*i)++;
	word = gc_substr(line, start, *i - start, &(sys->garbage));
	if (!word)
		return ;
	if (is_option(word) && !is_quoted_content(word))
		token_type = OPTIONS;
	else
		token_type = CMD;
	*lst = add_token(*lst, word, token_type, sys);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:08:22 by emetel            #+#    #+#             */
/*   Updated: 2025/08/03 18:53:43 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_option(char *word)
{
	if (!word || !word[0])
		return (0);
	if (word[0] == '-' && word[1] != '\0')
	{
		if (word[1] == '-' && word[2] == '\0')
			return (0);
		return (1);
	}
	return (0);
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

void	handle_pipe(char *line, int *i, t_type **lst)
{
	char	*symbol;

	(void)line;
	symbol = ft_strdup("|");
	*lst = add_token(*lst, symbol, PIPE);
	free(symbol);
	(*i)++;
}

void	handle_quote(char *line, int *i, t_type **lst, char quote)
{
	int		start;
	char	*word;
	t_token	token_type;

	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
	{
		*i = start;
		return ;
	}
	word = ft_substr(line, start, (*i - start) + 1);
	if (quote == '\'')
		token_type = SINGLE_QUOTE;
	else
		token_type = DOUBLE_QUOTE;
	*lst = add_token(*lst, word, token_type);
	free(word);
	(*i)++;
}

void	handle_word(char *line, int *i, t_type **lst)
{
	int		start;
	char	*word;
	t_token	token_type;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>'
		&& line[*i] != '\'' && line[*i] != '\"')
		(*i)++;
	word = ft_substr(line, start, *i - start);
	if (!word)
		return ;
	if (is_option(word) && !is_quoted_content(word))
		token_type = OPTIONS;
	else
		token_type = CMD;
	*lst = add_token(*lst, word, token_type);
	free(word);
}

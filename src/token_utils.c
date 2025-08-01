/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:08:22 by emetel            #+#    #+#             */
/*   Updated: 2025/08/01 02:24:38 by mkettab          ###   ########.fr       */
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

void	handle_pipe(char *line, int *i, t_type **lst, t_sys *sys)
{
	char	*symbol;

	(void)line;
	symbol = ft_strdup("|");
	*lst = add_token(*lst, symbol, PIPE, sys);
	free(symbol);
	(*i)++;
}

void	handle_quote(char *line, int *i, t_type **lst, char quote)
{
	int		start;
	char	*word;

	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
	{
		if (quote == '\'')
			printf("syntax error: unclosed single quote\n");
		else
			printf("syntax error: unclosed double quote\n");
		return ;
	}
	word = ft_substr(line, start, *i - start);
	*lst = add_token(*lst, word, CMD, sys);
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
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:08:22 by emetel            #+#    #+#             */
/*   Updated: 2025/05/22 02:15:53 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	word = ft_substr(line, start, *i - start);
	*lst = add_token(*lst, word, CMD);
	free(word);
	if (line[*i] == quote)
		(*i)++;
}

void	handle_word(char *line, int *i, t_type **lst)
{
	int		start;
	char	*word;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
		(*i)++;
	word = ft_substr(line, start, *i - start);
	*lst = add_token(*lst, word, CMD);
	free(word);
}

void	handle_redirection(char *line, int *i, t_type **lst)
{
	char	*symbol;
	t_token	type;

	if (line[*i + 1] == line[*i])
	{
		symbol = ft_substr(line, *i, 2);
		if (line[*i] == '<')
			type = HEREDOC;
		else
			type = APPEND;
		(*i) += 2;
	}
	else
	{
		symbol = ft_substr(line, *i, 1);
		if (line[*i] == '<')
			type = IN;
		else
			type = TRUNCATE;
		(*i)++;
	}
	*lst = add_token(*lst, symbol, type);
	free(symbol);
}

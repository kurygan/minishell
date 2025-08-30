/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:15:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 14:58:25 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*extract_quoted_content(char *line, int *i, char quote, t_sys *sys)
{
	int		start;
	char	*content;

	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
	{
		*i = start - 1;
		return (NULL);
	}
	content = gc_substr(line, start, *i - start, &(sys->garbage));
	(*i)++;
	return (content);
}

static char	*add_unquoted_suffix(char *line, int *i, char *word, t_sys *sys)
{
	int		start;
	char	*suffix;

	start = *i;
	if (line[start] != ' ' && line[start] != '\t')
	{
		while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
			&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
			(*i)++;
		suffix = gc_substr(line, start, *i - start, &(sys->garbage));
		return (gc_strjoin(word, suffix, &(sys->garbage)));
	}
	return (word);
}

void	handle_quote(char *line, int *i, t_type **lst, t_sys *sys)
{
	char	*word;
	char	quote;
	t_token	token_type;

	quote = line[*i];
	word = extract_quoted_content(line, i, quote, sys);
	if (!word)
		return ;
	word = add_unquoted_suffix(line, i, word, sys);
	if (quote == '\'')
		token_type = SINGLE_QUOTE;
	else
		token_type = DOUBLE_QUOTE;
	*lst = add_token(*lst, word, token_type, sys);
}

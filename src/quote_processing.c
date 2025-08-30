/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 00:00:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 11:53:49 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*extract_quote_content(char *line, int *i, char quote, t_sys *sys)
{
	char	*temp;
	int		start;

	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i])
	{
		temp = gc_substr(line, start, *i - start, &(sys->garbage));
		(*i)++;
		return (temp);
	}
	return (gc_strdup("", &(sys->garbage)));
}

static char	*extract_regular_text(char *line, int *i, t_sys *sys)
{
	char	*temp;
	int		start;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>'
		&& line[*i] != '\'' && line[*i] != '\"')
		(*i)++;
	temp = gc_substr(line, start, *i - start, &(sys->garbage));
	return (temp);
}

char	*extract_complete_word(char *line, int *i, t_sys *sys)
{
	char	*result;
	char	*temp;

	result = gc_strdup("", &(sys->garbage));
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
	{
		if (line[*i] == '\'' || line[*i] == '\"')
		{
			temp = extract_quote_content(line, i, line[*i], sys);
			result = gc_strjoin(result, temp, &(sys->garbage));
		}
		else
		{
			temp = extract_regular_text(line, i, sys);
			result = gc_strjoin(result, temp, &(sys->garbage));
		}
	}
	return (result);
}

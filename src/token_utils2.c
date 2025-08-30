/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:10:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 14:58:25 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*extract_quoted_part(char *line, int *i, char quote, t_sys *sys)
{
	int		start;
	char	*result;

	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	result = gc_substr(line, start, *i - start + 1, &sys->garbage);
	(*i)++;
	return (result);
}

static char	*extract_unquoted_suffix(char *line, int *i, t_sys *sys)
{
	int		start;
	char	*result;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
		(*i)++;
	if (start < *i)
		result = gc_substr(line, start, *i - start, &(sys->garbage));
	else
		result = NULL;
	if (line[*i])
		(*i)++;
	return (result);
}

char	*extract_quoted_arg(char *line, int *i, char quote, t_sys *sys)
{
	char	*quoted_part;
	char	*suffix;

	quoted_part = extract_quoted_part(line, i, quote, sys);
	if (line[*i] != ' ' && line[*i] != '\t')
	{
		suffix = extract_unquoted_suffix(line, i, sys);
		if (suffix)
			return (gc_strjoin(quoted_part, suffix, &(sys->garbage)));
	}
	return (quoted_part);
}

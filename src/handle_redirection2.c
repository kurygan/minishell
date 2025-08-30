/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:35:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 15:35:00 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*extract_quoted_redir_content(char *line, int *i, char quote, \
	t_sys *sys)
{
	int		start;
	char	*target[2];

	(*i)++;
	start = *i;
	target[0] = gc_strdup("", &sys->garbage);
	while (line[*i] && line[*i] != quote)
	{
		if (line[*i] == '\'' && quote != '\'')
		{
			target[1] = gc_substr(line, start, *i - start, &sys->garbage);
			target[0] = gc_strjoin(target[0], target[1], &sys->garbage);
			(*i)++;
			start = *i;
		}
		else
			(*i)++;
	}
	target[1] = gc_substr(line, start, *i - start, &sys->garbage);
	target[0] = gc_strjoin(target[0], target[1], &sys->garbage);
	(*i)++;
	return (target[0]);
}

char	*append_unquoted_suffix(char *line, int *i, char *target, \
	t_sys *sys)
{
	int		start;
	char	*suffix;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
		(*i)++;
	if (start < *i)
	{
		suffix = gc_substr(line, start, *i - start, &(sys->garbage));
		target = gc_strjoin(target, suffix, &(sys->garbage));
	}
	if (line[*i])
		(*i)++;
	return (target);
}

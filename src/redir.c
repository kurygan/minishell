/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 01:33:31 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/30 14:58:25 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*process_dollar_var(char *line, int *i, int *start, t_sys *sys)
{
	char	*result;

	*start = *i;
	(*i)++;
	while (ft_isalnum(line[*i]) || line[*i] == '_')
		(*i)++;
	result = expand_var(gc_substr(line, *start, *i, &(sys->garbage)), \
			sys, sys->exit_status);
	*start = *i;
	return (result);
}

char	*expand_heredoc(char *line, t_sys *sys)
{
	int		i;
	int		start;
	char	*result;

	(void)0, i = 0, start = 0;
	result = gc_strdup("", &(sys->garbage));
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (i > start)
				result = gc_strjoin(result, gc_substr(line, start, i, \
						&(sys->garbage)), &(sys->garbage));
			result = gc_strjoin(result, process_dollar_var(line, &i, \
					&start, sys), &(sys->garbage));
		}
		else
			i++;
	}
	if (i > start)
		result = gc_strjoin(result, gc_substr(line, start, i, \
				&(sys->garbage)), &(sys->garbage));
	if (!result[0])
		result = gc_strdup(line, &(sys->garbage));
	return (result);
}

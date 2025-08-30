/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:41:46 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 15:27:51 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_mixed_quotes_in_quoted(char *original, int *i)
{
	char	quote;

	quote = original[*i];
	(*i)++;
	while (original[*i] && original[*i] != quote)
		(*i)++;
	if (original[*i])
		(*i)++;
	if (original[*i] && original[*i] != ' ' && original[*i] != '\t')
		return (1);
	return (0);
}

int	check_mixed_quotes_in_unquoted(char *original, int *i)
{
	int	start_text;

	start_text = *i;
	while (original[*i] && original[*i] != '\'' && original[*i] != '\"')
		(*i)++;
	if (original[*i] && *i > start_text)
		return (1);
	return (0);
}

int	has_mixed_quotes(char *original)
{
	int	i;

	i = 0;
	while (original[i])
	{
		if (original[i] == '\'' || original[i] == '\"')
		{
			if (check_mixed_quotes_in_quoted(original, &i))
				return (1);
		}
		else
		{
			if (check_mixed_quotes_in_unquoted(original, &i))
				return (1);
		}
	}
	return (0);
}

int	process_quoted_part(char *str, int *i, char **result, t_sys *sys)
{
	int		start;
	char	quote;
	char	*part;
	char	*temp;

	start = *i;
	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i])
		(*i)++;
	part = gc_substr(str, start, *i - start, &(sys->garbage));
	temp = process_quoted_arg(part, sys, sys->exit_status);
	*result = gc_strjoin(*result, temp, &(sys->garbage));
	return (1);
}

int	process_unquoted_part(char *str, int *i, char **result, t_sys *sys)
{
	int		start;
	char	*part;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '\"')
		(*i)++;
	if (*i > start)
	{
		part = gc_substr(str, start, *i - start, &(sys->garbage));
		if (part[0] == '$')
			expand_variable_str(&part, sys, sys->exit_status);
		else if (part[0] == '~')
			part = expand_tilde(part, sys);
		*result = gc_strjoin(*result, part, &(sys->garbage));
	}
	return (1);
}

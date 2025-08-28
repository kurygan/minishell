/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:12:30 by emetel            #+#    #+#             */
/*   Updated: 2025/08/27 15:55:39 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*handle_exit_status(char *result, int exit_status, int *i, \
				t_gc **garbage)
{
	char	*temp;

	temp = gc_itoa(exit_status, garbage);
	result = gc_strjoin(result, temp, garbage);
	*i += 2;
	return (result);
}

static char	*handle_variable(char *content, char *result, t_sys *sys, int *i)
{
	int		start;

	start = *i + 1;
	while (content[start] && (ft_isalnum(content[start])
			|| content[start] == '_'))
		start++;
	if (start > *i + 1)
		return (process_valid_variable(content, result, sys, i));
	else
		return (process_invalid_variable(content, result, i, &(sys->garbage)));
}

char	*expand_variables_in_dquotes(char *content, t_sys *sys,
	int exit_status)
{
	char	*result;
	int		i;

	if (!content)
		return (gc_strdup("", &(sys->garbage)));
	result = gc_strdup("", &(sys->garbage));
	i = 0;
	while (content[i])
	{
		if (content[i] == '$')
		{
			if (content[i + 1] == '?')
				result = handle_exit_status(result, exit_status, &i, \
						&(sys->garbage));
			else
				result = handle_variable(content, result, sys, &i);
		}
		else
			result = process_regular_char(content, result, &i, &(sys->garbage));
	}
	return (result);
}

char	*expand_quote(char *arg, t_sys *sys, int exit_status,
	int is_single_quote)
{
	char	*content;
	char	*result;

	if (!arg)
		return (gc_strdup("", &(sys->garbage)));
	content = remove_quotes(arg, sys);
	if (is_single_quote)
		result = gc_strdup(content, &(sys->garbage));
	else
		result = expand_variables_in_dquotes(content, sys, exit_status);
	gc_free(content, &(sys->garbage));
	return (result);
}

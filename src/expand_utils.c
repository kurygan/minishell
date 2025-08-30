/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:00:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 14:39:40 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*process_var_expansion(char *arg, int *i, t_sys *sys, \
				int exit_status)
{
	char	*result;
	char	*var_name;
	char	*value;
	int		start;

	(void)exit_status;
	result = gc_strdup("", &(sys->garbage));
	if (arg[*i + 1] == '?')
	{
		value = gc_itoa(sys->exit_status, &(sys->garbage));
		result = gc_strjoin(result, value, &(sys->garbage));
		*i += 2;
	}
	else
	{
		start = *i + 1;
		while (arg[start] && (ft_isalnum(arg[start])
				|| arg[start] == '_'))
			start++;
		var_name = gc_substr(arg, *i + 1, start - *i - 1, &(sys->garbage));
		value = get_env_value_from_list(var_name, sys->env_list);
		if (value)
			result = gc_strjoin(result, gc_strdup(value, &(sys->garbage)),
					&(sys->garbage));
		gc_free(var_name, &(sys->garbage));
		*i = start;
	}
	return (result);
}

char	*expand_var(char *arg, t_sys *sys, int exit_status)
{
	char	*result;
	char	*temp;
	int		i;

	if (!arg || arg[0] != '$')
		return (gc_strdup(arg, &(sys->garbage)));
	result = gc_strdup("", &(sys->garbage));
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			temp = process_var_expansion(arg, &i, sys, exit_status);
			result = gc_strjoin(result, temp, &(sys->garbage));
		}
		else
		{
			temp = gc_substr(arg, i, 1, &(sys->garbage));
			result = gc_strjoin(result, temp, &(sys->garbage));
			i++;
		}
	}
	return (result);
}

void	expand_quoted_str(char **str, t_sys *sys, int exit_status,
	int is_single)
{
	char	*expanded;

	expanded = expand_quote(*str, sys, exit_status, is_single);
	gc_free(*str, &(sys->garbage));
	*str = expanded;
}

void	expand_variable_str(char **str, t_sys *sys, int exit_status)
{
	char	*expanded;

	expanded = expand_var(*str, sys, exit_status);
	*str = expanded;
}

char	*extract_var_content(char *content, int *i, int start, t_gc **garbage)
{
	char	*temp;

	temp = gc_substr(content, *i + 1, start - *i - 1, garbage);
	*i = start;
	return (temp);
}

char	*process_quoted_arg(char *arg, t_sys *sys, int exit_status)
{
	char	*result;
	char	quote_type;
	size_t	len;
	char	*content;

	if (!arg)
		return (gc_strdup("", &(sys->garbage)));
	len = ft_strlen(arg);
	if (len < 2)
		return (gc_strdup(arg, &(sys->garbage)));
	if (arg[0] == '\'' && arg[len - 1] == '\'')
		quote_type = '\'';
	else if (arg[0] == '\"' && arg[len - 1] == '\"')
		quote_type = '\"';
	else
		return (gc_strdup(arg, &(sys->garbage)));
	if (quote_type == '\'')
	{
		result = gc_substr(arg, 1, len - 2, &(sys->garbage));
		return (result);
	}
	if (quote_type == '\"')
	{
		content = gc_substr(arg, 1, len - 2, &(sys->garbage));
		result = expand_variables_in_dquotes(content, sys, exit_status);
		gc_free(content, &(sys->garbage));
		return (result);
	}
	return (gc_strdup(arg, &(sys->garbage)));
}

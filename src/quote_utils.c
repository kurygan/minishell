/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:00:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/25 14:23:27 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*remove_quotes(char *str, t_sys *sys)
{
	int		len;
	char	*result;

	if (!str || !str[0])
		return (gc_strdup("", &(sys->garbage)));
	len = ft_strlen(str);
	if (len < 2)
		return (gc_strdup(str, &(sys->garbage)));
	if ((str[0] == '\'' || str[0] == '\"') && str[len - 1] == str[0])
	{
		result = gc_substr(str, 1, len - 2, &(sys->garbage));
		return (result);
	}
	return (gc_strdup(str, &(sys->garbage)));
}

char	*process_regular_char(char *content, char *result, int *i, \
			t_gc **garbage)
{
	char	*temp;

	temp = gc_substr(content, *i, 1, garbage);
	result = gc_strjoin(result, temp, garbage);
	(*i)++;
	return (result);
}

char	*process_valid_variable(char *content, char *result, t_sys *sys, int *i)
{
	char	*temp;
	char	*var_value;
	int		start;

	start = *i + 1;
	while (content[start] && (ft_isalnum(content[start])
			|| content[start] == '_'))
		start++;
	temp = extract_var_content(content, i, start, &(sys->garbage));
	var_value = get_env_value_from_list(temp, sys->env_list);
	if (var_value)
		result = gc_strjoin(result, gc_strdup(var_value, &(sys->garbage)), \
				&(sys->garbage));
	gc_free(temp, &(sys->garbage));
	return (result);
}

char	*process_invalid_variable(char *content, char *result, int *i, \
			t_gc **garbage)
{
	char	*temp;

	temp = gc_substr(content, *i, 1, garbage);
	result = gc_strjoin(result, temp, garbage);
	(*i)++;
	return (result);
}

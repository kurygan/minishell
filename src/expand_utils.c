/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:00:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/24 21:42:23 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*expand_var(char *arg, t_sys *sys, int exit_status)
{
	char	*var_name;
	char	*value;

	if (!arg || arg[0] != '$')
		return (gc_strdup(arg, &(sys->garbage)));
	if (arg[1] == '?')
		return (gc_itoa(exit_status, &(sys->garbage)));
	var_name = arg + 1;
	value = get_env_value_from_list(var_name, sys->env_list);
	if (value)
		return (gc_strdup(value, &(sys->garbage)));
	return (gc_strdup("", &(sys->garbage)));
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

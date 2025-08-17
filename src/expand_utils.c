/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:00:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/17 02:17:04 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*expand_var(char *arg, t_sys *sys, int exit_status)
{
	int		i;
	char	*var_name;
	char	*value;
	size_t	len;

	if (!arg || arg[0] != '$')
		return (gc_strdup(arg, &(sys->garbage)));
	if (arg[1] == '?')
		return (gc_itoa(exit_status, &(sys->garbage)));
	var_name = arg + 1;
	len = ft_strlen(var_name);
	i = 0;
	while (sys->env[i])
	{
		if (!ft_strncmp(sys->env[i], var_name, len) && sys->env[i][len] == '=')
		{
			value = sys->env[i] + len + 1;
			return (gc_strdup(value, &(sys->garbage)));
		}
		i++;
	}
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

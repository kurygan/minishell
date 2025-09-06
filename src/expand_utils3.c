/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:00:00 by mkettab           #+#    #+#             */
/*   Updated: 2025/09/06 15:02:34 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*process_single_quote(char *arg, t_sys *sys)
{
	size_t	len;

	len = ft_strlen(arg);
	return (gc_substr(arg, 1, len - 2, &(sys->garbage)));
}

static char	*process_double_quote(char *arg, t_sys *sys, int exit_status)
{
	char	*content;
	char	*result;
	size_t	len;

	len = ft_strlen(arg);
	content = gc_substr(arg, 1, len - 2, &(sys->garbage));
	result = expand_variables_in_dquotes(content, sys, exit_status);
	gc_free(content, &(sys->garbage));
	return (result);
}

char	*process_quoted_arg(char *arg, t_sys *sys, int exit_status)
{
	char	quote_type;
	size_t	len;

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
		return (process_single_quote(arg, sys));
	if (quote_type == '\"')
		return (process_double_quote(arg, sys, exit_status));
	return (gc_strdup(arg, &(sys->garbage)));
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:00:00 by emetel            #+#    #+#             */
/*   Updated: 2025/09/06 15:02:34 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*expand_regular_var(char *arg, int *i, t_sys *sys)
{
	char	*var_name;
	char	*value;
	char	*result;
	int		start;

	start = *i + 1;
	while (arg[start] && (ft_isalnum(arg[start]) || arg[start] == '_'))
		start++;
	var_name = gc_substr(arg, *i + 1, start - *i - 1, &(sys->garbage));
	value = get_env_value_for_expansion(var_name, sys);
	if (value)
		result = gc_strdup(value, &(sys->garbage));
	else
		result = gc_strdup("", &(sys->garbage));
	gc_free(var_name, &(sys->garbage));
	*i = start;
	return (result);
}

static char	*process_var_expansion(char *arg, int *i, t_sys *sys, \
				int exit_status)
{
	(void)exit_status;
	if (arg[*i + 1] == '?')
		return (expand_exit_status_var(i, sys));
	else
		return (expand_regular_var(arg, i, sys));
}

static char	*process_single_char(char *arg, int *i, t_sys *sys)
{
	char	*temp;

	temp = gc_substr(arg, *i, 1, &(sys->garbage));
	(*i)++;
	return (temp);
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
			temp = process_single_char(arg, &i, sys);
			result = gc_strjoin(result, temp, &(sys->garbage));
		}
	}
	return (result);
}

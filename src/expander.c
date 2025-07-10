/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:50:01 by emetel            #+#    #+#             */
/*   Updated: 2025/06/23 20:50:13 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*expand_var(char *arg, t_sys *sys, int exit_status)
{
	int		i;
	char	*var_name;
	char	*value;
	size_t	len;
	char	**env;

	if (!arg || arg[0] != '$')
		return (gc_strdup(arg, &sys->gc, OTHER));
	if (arg[1] == '?')
		return (ft_itoa(exit_status));
	
	var_name = arg + 1;
	len = ft_strlen(var_name);
	i = 0;
	env = sys->env;
	while (env[i])
	{
		if (!ft_strcmp(env[i], var_name) && env[i][len] == '=')
		{
			value = env[i] + len + 1;
			return (gc_strdup(value, &sys->gc, OTHER));
		}
		i++;
	}
	return (gc_strdup("", &sys->gc, OTHER));
}

static void	expand_single_str(char **str, t_sys *sys, int exit_status)
{
	char	*expanded;

	if (*str && (*str)[0] == '$')
	{
		expanded = expand_var(*str, sys, exit_status);
		*str = expanded;
	}
}

static void	expand_str_array(char **arr, t_sys *sys, int exit_status)
{
	int		i;
	char	*expanded;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		if (arr[i][0] == '$')
		{
			expanded = expand_var(arr[i], sys, exit_status);
			arr[i] = expanded;
		}
		i++;
	}
}

void	expand_variables(t_cmd_segment *segments, t_sys *sys, int exit_status)
{
	while (segments)
	{
		expand_single_str(&segments->cmd, sys, exit_status);
		expand_str_array(segments->args, sys, exit_status);
		expand_str_array(segments->options, sys, exit_status);
		expand_single_str(&segments->infile, sys, exit_status);
		expand_single_str(&segments->outfile, sys, exit_status);
		segments = segments->next;
	}
}

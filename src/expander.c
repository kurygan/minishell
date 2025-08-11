/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:50:01 by emetel            #+#    #+#             */
/*   Updated: 2025/08/09 21:12:07 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	expand_single_str(char **str, t_sys *sys, int exit_status)
{
	char	*original;
	size_t	len;

	if (!*str)
		return ;
	original = *str;
	len = ft_strlen(original);
	if (original[0] == '\'' && original[len - 1] == '\'')
		expand_quoted_str(str, sys, exit_status, 1);
	else if (original[0] == '\"' && original[len - 1] == '\"')
		expand_quoted_str(str, sys, exit_status, 0);
	else if (original[0] == '$')
		expand_variable_str(str, sys, exit_status);
}

static void	expand_str_array(char **arr, t_sys *sys, int exit_status)
{
	(void)sys;
	int		i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		expand_single_str(&arr[i], sys, exit_status);
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

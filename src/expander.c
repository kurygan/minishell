/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:50:01 by emetel            #+#    #+#             */
/*   Updated: 2025/08/28 21:06:47 by emetel           ###   ########.fr       */
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

static void	expand_str_array(char **str, t_sys *sys, int exit_status)
{
	int		i;

	if (!str || !*str)
		return ;
	i = 0;
	while (str[i])
	{
		expand_single_str(&str[i], sys, exit_status);
		i++;
	}
}

void	expand_variables(t_cmd_segment *segments, t_sys *sys, int exit_status)
{
	t_type	*outfiles;

	while (segments)
	{
		outfiles = segments->outfiles;
		expand_single_str(&segments->cmd, sys, exit_status);
		expand_str_array(segments->args, sys, exit_status);
		expand_single_str(&segments->infile, sys, exit_status);
		while (outfiles)
		{
			expand_single_str(&(outfiles->str), sys, exit_status);
			outfiles = outfiles->next;
		}
		segments = segments->next;
	}
}

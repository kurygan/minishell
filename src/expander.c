/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:50:01 by emetel            #+#    #+#             */
/*   Updated: 2025/08/03 17:55:07 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	expand_single_str(char **str, char **env, int exit_status)
{
	char	*original;
	size_t	len;

	if (!*str)
		return ;
	original = *str;
	len = ft_strlen(original);
	if (original[0] == '\'' && original[len - 1] == '\'')
		expand_quoted_str(str, env, exit_status, 1);
	else if (original[0] == '\"' && original[len - 1] == '\"')
		expand_quoted_str(str, env, exit_status, 0);
	else if (original[0] == '$')
		expand_variable_str(str, env, exit_status);
}

static void	expand_str_array(char **arr, char **env, int exit_status)
{
	int		i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		expand_single_str(&arr[i], env, exit_status);
		i++;
	}
}

void	expand_variables(t_cmd_segment *segments, char **env, int exit_status)
{
	while (segments)
	{
		expand_single_str(&segments->cmd, env, exit_status);
		expand_str_array(segments->args, env, exit_status);
		expand_str_array(segments->options, env, exit_status);
		expand_single_str(&segments->infile, env, exit_status);
		expand_single_str(&segments->outfile, env, exit_status);
		segments = segments->next;
	}
}

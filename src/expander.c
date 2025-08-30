/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:50:01 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 14:46:09 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*expand_mixed_quotes(char *str, t_sys *sys)
{
	int		i;
	char	*result;

	if (!str)
		return (NULL);
	result = gc_strdup("", &(sys->garbage));
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			process_quoted_part(str, &i, &result, sys);
		else
			process_unquoted_part(str, &i, &result, sys);
	}
	return (result);
}

static void	expand_single_str(char **str, t_sys *sys)
{
	char	*original;
	size_t	len;

	if (!*str)
		return ;
	original = *str;
	len = ft_strlen(original);
	if (has_mixed_quotes(original))
		*str = expand_mixed_quotes(original, sys);
	else if (original[0] == '\'' && original[len - 1] == '\'')
		*str = process_quoted_arg(original, sys, sys->exit_status);
	else if (original[0] == '\"' && original[len - 1] == '\"')
		*str = process_quoted_arg(original, sys, sys->exit_status);
	else if (original[0] == '$')
		expand_variable_str(str, sys, sys->exit_status);
	else if (original[0] == '~')
		*str = expand_tilde(original, sys);
}

static void	expand_quoted_token(char **str, t_sys *sys)
{
	char	*original;
	size_t	len;

	if (!*str)
		return ;
	original = *str;
	len = ft_strlen(original);
	if (original[0] == '\'' && original[len - 1] == '\'')
		*str = process_quoted_arg(original, sys, sys->exit_status);
	else if (original[0] == '\"' && original[len - 1] == '\"')
		*str = process_quoted_arg(original, sys, sys->exit_status);
}

static void	expand_str_array(char **str, t_sys *sys)
{
	int		i;

	if (!str || !*str)
		return ;
	i = 0;
	while (str[i])
	{
		expand_single_str(&str[i], sys);
		i++;
	}
}

void	expand_variables(t_cmd_segment *segments, t_sys *sys, int exit_status)
{
	t_type	*outfiles;
	int		old_exit_status;

	old_exit_status = sys->exit_status;
	sys->exit_status = exit_status;
	while (segments)
	{
		outfiles = segments->outfiles;
		if (segments->cmd && ((segments->cmd[0] == '\'' \
			&& segments->cmd[ft_strlen(segments->cmd) - 1] == '\'') \
			|| (segments->cmd[0] == '\"' \
				&& segments->cmd[ft_strlen(segments->cmd) - 1] == '\"')))
			expand_quoted_token(&segments->cmd, sys);
		else
			expand_single_str(&segments->cmd, sys);
		expand_str_array(segments->args, sys);
		expand_single_str(&segments->infile, sys);
		while (outfiles)
		{
			expand_single_str(&(outfiles->str), sys);
			outfiles = outfiles->next;
		}
		segments = segments->next;
	}
	sys->exit_status = old_exit_status;
}

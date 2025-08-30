/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:50:01 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 12:51:02 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*expand_mixed_quotes(char *str, t_sys *sys, int exit_status)
{
	int		i;
	char	*result;
	char	*temp;
	char	*part;
	int		start;

	if (!str)
		return (NULL);
	result = gc_strdup("", &(sys->garbage));
	i = 0;
	while (str[i])
	{
		start = i;
		if (str[i] == '\'' || str[i] == '\"')
		{
			char quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i])
				i++;
			part = gc_substr(str, start, i - start, &(sys->garbage));
			temp = process_quoted_arg(part, sys, exit_status);
			result = gc_strjoin(result, temp, &(sys->garbage));
		}
		else
		{
			while (str[i] && str[i] != '\'' && str[i] != '\"')
				i++;
			if (i > start)
			{
				part = gc_substr(str, start, i - start, &(sys->garbage));
				if (part[0] == '$')
					expand_variable_str(&part, sys, exit_status);
				else if (part[0] == '~')
					part = expand_tilde(part, sys);
				result = gc_strjoin(result, part, &(sys->garbage));
			}
		}
	}
	return (result);
}

static void	expand_single_str(char **str, t_sys *sys, int exit_status)
{
	char	*original;
	size_t	len;
	int		has_mixed_quotes;
	int		i;

	if (!*str)
		return ;
	original = *str;
	len = ft_strlen(original);
	
	// Check if string contains mixed quotes or quotes with adjacent text
	has_mixed_quotes = 0;
	i = 0;
	while (original[i])
	{
		if (original[i] == '\'' || original[i] == '\"')
		{
			char quote = original[i];
			i++;
			while (original[i] && original[i] != quote)
				i++;
			if (original[i])
				i++;
			// If there's text after the closing quote, it's mixed
			if (original[i] && original[i] != ' ' && original[i] != '\t')
			{
				has_mixed_quotes = 1;
				break;
			}
		}
		else
		{
			// If we find text before quotes, it's mixed
			int start_text = i;
			while (original[i] && original[i] != '\'' && original[i] != '\"')
				i++;
			if (original[i] && i > start_text)
			{
				has_mixed_quotes = 1;
				break;
			}
		}
	}
	
	if (has_mixed_quotes)
		*str = expand_mixed_quotes(original, sys, exit_status);
	else if (original[0] == '\'' && original[len - 1] == '\'')
		*str = process_quoted_arg(original, sys, exit_status);
	else if (original[0] == '\"' && original[len - 1] == '\"')
		*str = process_quoted_arg(original, sys, exit_status);
	else if (original[0] == '$')
		expand_variable_str(str, sys, exit_status);
	else if (original[0] == '~')
		*str = expand_tilde(original, sys);
}

static void	expand_quoted_token(char **str, t_sys *sys, int exit_status)
{
	char	*original;
	size_t	len;

	if (!*str)
		return ;
	original = *str;
	len = ft_strlen(original);
	if (original[0] == '\'' && original[len - 1] == '\'')
		*str = process_quoted_arg(original, sys, exit_status);
	else if (original[0] == '\"' && original[len - 1] == '\"')
		*str = process_quoted_arg(original, sys, exit_status);
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
		// Handle fully quoted tokens specifically
		if (segments->cmd && 
			((segments->cmd[0] == '\'' && segments->cmd[ft_strlen(segments->cmd) - 1] == '\'') ||
			 (segments->cmd[0] == '\"' && segments->cmd[ft_strlen(segments->cmd) - 1] == '\"')))
			expand_quoted_token(&segments->cmd, sys, exit_status);
		else
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

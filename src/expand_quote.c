/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:12:30 by emetel            #+#    #+#             */
/*   Updated: 2025/08/03 18:00:50 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*handle_exit_status(char *result, int exit_status, int *i)
{
	char	*temp;

	temp = ft_itoa(exit_status);
	result = ft_strjoin_free(result, temp);
	free(temp);
	*i += 2;
	return (result);
}

static char	*handle_variable(char *content, char *result, char **env, int *i)
{
	int		start;

	start = *i + 1;
	while (content[start] && (ft_isalnum(content[start])
			|| content[start] == '_'))
		start++;
	if (start > *i + 1)
		return (process_valid_variable(content, result, env, i));
	else
		return (process_invalid_variable(content, result, i));
}

static char	*expand_variables_in_dquotes(char *content, char **env,
	int exit_status)
{
	char	*result;
	int		i;

	if (!content)
		return (ft_strdup(""));
	result = ft_strdup("");
	i = 0;
	while (content[i])
	{
		if (content[i] == '$')
		{
			if (content[i + 1] == '?')
				result = handle_exit_status(result, exit_status, &i);
			else
				result = handle_variable(content, result, env, &i);
		}
		else
			result = process_regular_char(content, result, &i);
	}
	return (result);
}

char	*expand_quote(char *arg, char **env, int exit_status,
	int is_single_quote)
{
	char	*content;
	char	*result;

	if (!arg)
		return (ft_strdup(""));
	content = remove_quotes(arg);
	if (is_single_quote)
		result = ft_strdup(content);
	else
		result = expand_variables_in_dquotes(content, env, exit_status);
	free(content);
	return (result);
}

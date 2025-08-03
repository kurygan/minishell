/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:00:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/03 18:00:50 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*expand_var(char *arg, char **env, int exit_status)
{
	int		i;
	char	*var_name;
	char	*value;
	size_t	len;

	if (!arg || arg[0] != '$')
		return (ft_strdup(arg));
	if (arg[1] == '?')
		return (ft_itoa(exit_status));
	var_name = arg + 1;
	len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, len) && env[i][len] == '=')
		{
			value = env[i] + len + 1;
			return (ft_strdup(value));
		}
		i++;
	}
	return (ft_strdup(""));
}

void	expand_quoted_str(char **str, char **env, int exit_status,
	int is_single)
{
	char	*expanded;

	expanded = expand_quote(*str, env, exit_status, is_single);
	free(*str);
	*str = expanded;
}

void	expand_variable_str(char **str, char **env, int exit_status)
{
	char	*expanded;

	expanded = expand_var(*str, env, exit_status);
	free(*str);
	*str = expanded;
}

char	*extract_var_content(char *content, int *i, int start)
{
	char	*temp;

	temp = ft_substr(content, *i + 1, start - *i - 1);
	*i = start;
	return (temp);
}

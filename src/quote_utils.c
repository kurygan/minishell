/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:00:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/03 18:00:56 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_env_value(char *var_name, char **env)
{
	int		i;
	size_t	len;

	if (!var_name || !env)
		return (NULL);
	len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, len) && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*remove_quotes(char *str)
{
	int		len;
	char	*result;

	if (!str || !str[0])
		return (ft_strdup(""));
	len = ft_strlen(str);
	if (len < 2)
		return (ft_strdup(str));
	if ((str[0] == '\'' || str[0] == '\"') && str[len - 1] == str[0])
	{
		result = ft_substr(str, 1, len - 2);
		return (result);
	}
	return (ft_strdup(str));
}

char	*process_regular_char(char *content, char *result, int *i)
{
	char	*temp;

	temp = ft_substr(content, *i, 1);
	result = ft_strjoin_free(result, temp);
	(*i)++;
	return (result);
}

char	*process_valid_variable(char *content, char *result, char **env, int *i)
{
	char	*temp;
	char	*var_value;
	int		start;

	start = *i + 1;
	while (content[start] && (ft_isalnum(content[start])
			|| content[start] == '_'))
		start++;
	temp = extract_var_content(content, i, start);
	var_value = get_env_value(temp, env);
	if (var_value)
		result = ft_strjoin_free(result, ft_strdup(var_value));
	free(temp);
	return (result);
}

char	*process_invalid_variable(char *content, char *result, int *i)
{
	char	*temp;

	temp = ft_substr(content, *i, 1);
	result = ft_strjoin_free(result, temp);
	(*i)++;
	return (result);
}

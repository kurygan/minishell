/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 16:00:00 by emetel            #+#    #+#             */
/*   Updated: 2025/09/06 15:20:01 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*process_plus_equal_raw_value(char *raw_value, char **value)
{
	if (raw_value && (*raw_value == ' ' || *raw_value == '\t'))
	{
		while (*raw_value == ' ' || *raw_value == '\t')
			raw_value++;
		if (!*raw_value)
		{
			*value = NULL;
			return (NULL);
		}
	}
	return (raw_value);
}

static char	*get_plus_equal_final_value(char *append_value, \
			t_env_var *existing_var, t_sys *sys)
{
	if (existing_var && existing_var->value && append_value)
		return (gc_strjoin(existing_var->value, append_value, &(sys->env_gc)));
	else if (append_value)
		return (gc_strdup(append_value, &(sys->env_gc)));
	else
		return (NULL);
}

char	*handle_plus_equal(char *arg, char **value, t_sys *sys)
{
	char		*equal_pos;
	char		*key;
	char		*raw_value;
	char		*append_value;
	t_env_var	*existing_var;

	equal_pos = ft_strchr(arg, '=');
	key = gc_substr(arg, 0, equal_pos - 1 - arg, &(sys->garbage));
	raw_value = gc_strdup(equal_pos + 2, &(sys->garbage));
	raw_value = process_plus_equal_raw_value(raw_value, value);
	if (raw_value == NULL)
		return (key);
	append_value = remove_quotes(raw_value, sys);
	existing_var = find_env_var(sys->export_list, key);
	*value = get_plus_equal_final_value(append_value, existing_var, sys);
	return (key);
}

bool	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str || (!ft_isalpha(*str) && *str != '_'))
		return (false);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

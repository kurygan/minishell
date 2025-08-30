/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:55:06 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 14:39:40 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_exported_vars(t_env_var *env_list)
{
	int			count;
	t_env_var	*current;

	count = 0;
	current = env_list;
	while (current)
	{
		if (current->exported)
			count++;
		current = current->next;
	}
	return (count);
}

void	sort_env_array(t_env_var **array, int size)
{
	int			i;
	int			j;
	t_env_var	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (ft_strcmp(array[j]->key, array[j + 1]->key) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_sorted_export_list(t_env_var **array, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(array[j]->key, 1);
		if (array[j]->value)
		{
			ft_putchar_fd('=', 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(array[j]->value, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		j++;
	}
}

static char	*skip_leading_whitespace(char *raw_value, char **value)
{
	while (*raw_value == ' ' || *raw_value == '\t')
		raw_value++;
	if (!*raw_value)
	{
		*value = NULL;
		return (NULL);
	}
	return (raw_value);
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
	if (raw_value && (*raw_value == ' ' || *raw_value == '\t'))
		raw_value = skip_leading_whitespace(raw_value, value);
	if (raw_value == NULL)
		return (key);
	append_value = remove_quotes(raw_value, sys);
	existing_var = find_env_var(sys->env_list, key);
	if (existing_var && existing_var->value && append_value)
		*value = gc_strjoin(existing_var->value, append_value, &(sys->env_gc));
	else if (append_value)
		*value = gc_strdup(append_value, &(sys->env_gc));
	else
		*value = NULL;
	return (key);
}

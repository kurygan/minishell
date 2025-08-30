/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:55:06 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 16:04:47 by emetel           ###   ########.fr       */
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

static char	*process_raw_value_export(char *raw_value, t_sys *sys)
{
	if (raw_value && (*raw_value == ' ' || *raw_value == '\t'))
	{
		while (*raw_value == ' ' || *raw_value == '\t')
			raw_value++;
		if (!*raw_value)
			return (NULL);
	}
	return (remove_quotes(raw_value, sys));
}

char	*extract_key_value(char *arg, char **value, t_sys *sys)
{
	char		*equal_pos;
	char		*plus_equal_pos;
	char		*key;
	char		*raw_value;

	plus_equal_pos = ft_strnstr(arg, "+=", ft_strlen(arg));
	equal_pos = ft_strchr(arg, '=');
	if (!equal_pos)
	{
		*value = NULL;
		return (gc_strdup(arg, &(sys->garbage)));
	}
	if (plus_equal_pos && plus_equal_pos == equal_pos)
		return (handle_plus_equal(arg, value, sys));
	key = gc_substr(arg, 0, equal_pos - arg, &(sys->garbage));
	raw_value = gc_strdup(equal_pos + 1, &(sys->garbage));
	*value = process_raw_value_export(raw_value, sys);
	return (key);
}

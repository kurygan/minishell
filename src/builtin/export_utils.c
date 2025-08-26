/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:55:06 by emetel            #+#    #+#             */
/*   Updated: 2025/08/26 23:23:13 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	if (!ft_isalpha(*str) && *str != '_')
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

char	*extract_key_value(char *arg, char **value, t_sys *sys)
{
	char	*equal_pos;
	char	*key;
	char	*raw_value;

	equal_pos = ft_strchr(arg, '=');
	if (!equal_pos)
	{
		*value = NULL;
		return (gc_strdup(arg, &(sys->garbage)));
	}
	key = gc_substr(arg, 0, equal_pos - arg, &(sys->garbage));
	raw_value = gc_strdup(equal_pos + 1, &(sys->garbage));
	*value = remove_quotes(raw_value, sys);
	return (key);
}

void	insert_env_var_sorted(t_env_var **env_list, char *key, char *value, \
			t_sys *sys)
{
	t_env_var	*new_var;
	t_env_var	*current;
	t_env_var	*prev;

	new_var = create_env_var(key, value, sys);
	new_var->exported = true;
	if (!new_var)
		return ;
	if (!*env_list || ft_strcmp(new_var->key, (*env_list)->key) < 0)
	{
		new_var->next = *env_list;
		*env_list = new_var;
		return ;
	}
	current = *env_list;
	prev = NULL;
	while (current && ft_strcmp(new_var->key, current->key) > 0)
	{
		prev = current;
		current = current->next;
	}
	prev->next = new_var;
	new_var->next = current;
}

static int	count_exported_vars(t_env_var *env_list)
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

static void	sort_env_array(t_env_var **array, int size)
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

void	print_export_list(t_env_var *env_list, t_sys *sys)
{
	t_env_var	**array;
	t_env_var	*current;
	int			count;
	int			i;
	int			j;

	count = count_exported_vars(env_list);
	if (count == 0)
		return ;
	array = gc_malloc(&sys->garbage, sizeof(t_env_var *) * count);
	current = env_list;
	i = 0;
	while (current)
	{
		if (current->exported)
		{
			array[i] = current;
			i++;
		}
		current = current->next;
	}
	sort_env_array(array, count);
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

void	add_or_update_var(t_env_var **env_list, char *key, char *value, \
			t_sys *sys)
{
	t_env_var	*existing_var;

	existing_var = find_env_var(*env_list, key);
	if (existing_var)
	{
		update_env_var(existing_var, value, sys);
		existing_var->exported = true;
	}
	else
	{
		add_env_var_exported(env_list, key, value, sys);
	}
}

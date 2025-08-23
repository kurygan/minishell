/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:55:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/24 00:01:22 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env_var	*create_env_var(char *key, char *value, t_sys *sys)
{
	t_env_var	*new_var;

	new_var = gc_malloc(&sys->garbage, sizeof(t_env_var));
	if (!new_var)
		return (NULL);
	new_var->key = gc_strdup(key, &sys->garbage);
	if (value)
		new_var->value = gc_strdup(value, &sys->garbage);
	else
		new_var->value = NULL;
	new_var->next = NULL;
	return (new_var);
}

t_env_var	*parse_env_string(char *env_str, t_sys *sys)
{
	char		*equal_pos;
	char		*key;
	char		*value;
	t_env_var	*env_var;

	if (!env_str)
		return (NULL);
	equal_pos = ft_strchr(env_str, '=');
	if (!equal_pos)
		return (NULL);
	key = gc_substr(env_str, 0, equal_pos - env_str, &sys->garbage);
	value = gc_strdup(equal_pos + 1, &sys->garbage);
	env_var = create_env_var(key, value, sys);
	return (env_var);
}

t_env_var	*init_env_list(char **env, t_sys *sys)
{
	t_env_var	*head;
	t_env_var	*current;
	int			i;

	if (!env || !env[0])
		return (NULL);
	head = parse_env_string(env[0], sys);
	if (!head)
		return (NULL);
	current = head;
	i = 1;
	while (env[i])
	{
		current->next = parse_env_string(env[i], sys);
		if (current->next)
			current = current->next;
		i++;
	}
	return (head);
}

char	**env_list_to_array(t_env_var *env_list, t_sys *sys)
{
	char		**env_array;
	t_env_var	*current;
	int			count;
	int			i;

	count = 0;
	current = env_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	env_array = gc_malloc(&sys->garbage, sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		if (current->value)
		{
			env_array[i] = gc_strjoin(gc_strjoin(current->key, "=", \
				&sys->garbage), current->value, &sys->garbage);
		}
		else
			env_array[i] = gc_strdup(current->key, &sys->garbage);
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

t_env_var	*find_env_var(t_env_var *env_list, char *key)
{
	t_env_var	*current;

	if (!key)
		return (NULL);
	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	add_env_var(t_env_var **env_list, char *key, char *value, t_sys *sys)
{
	t_env_var	*new_var;
	t_env_var	*current;

	if (!key)
		return ;
	new_var = create_env_var(key, value, sys);
	if (!new_var)
		return ;
	if (!*env_list)
	{
		*env_list = new_var;
		return ;
	}
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new_var;
}

void	update_env_var(t_env_var *env_var, char *value, t_sys *sys)
{
	if (!env_var)
		return ;
	if (env_var->value)
		gc_free(env_var->value, &sys->garbage);
	if (value)
		env_var->value = gc_strdup(value, &sys->garbage);
	else
		env_var->value = NULL;
}

void	remove_env_var(t_env_var **env_list, char *key, t_sys *sys)
{
	t_env_var	*current;
	t_env_var	*prev;

	if (!*env_list || !key)
		return ;
	current = *env_list;
	if (ft_strcmp(current->key, key) == 0)
	{
		*env_list = current->next;
		gc_free(current->key, &sys->garbage);
		if (current->value)
			gc_free(current->value, &sys->garbage);
		gc_free(current, &sys->garbage);
		return ;
	}
	prev = current;
	current = current->next;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			prev->next = current->next;
			gc_free(current->key, &sys->garbage);
			if (current->value)
				gc_free(current->value, &sys->garbage);
			gc_free(current, &sys->garbage);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	free_env_list(t_env_var *env_list, t_sys *sys)
{
	t_env_var	*current;
	t_env_var	*next;

	current = env_list;
	while (current)
	{
		next = current->next;
		gc_free(current->key, &sys->garbage);
		if (current->value)
			gc_free(current->value, &sys->garbage);
		gc_free(current, &sys->garbage);
		current = next;
	}
}

char	*get_env_value_from_list(char *var_name, t_env_var *env_list)
{
	t_env_var	*current;

	if (!var_name || !env_list)
		return (NULL);
	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, var_name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

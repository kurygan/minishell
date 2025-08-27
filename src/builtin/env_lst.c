/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:32:14 by emetel            #+#    #+#             */
/*   Updated: 2025/08/27 15:55:39 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env_var	*create_env_var(char *key, char *value, t_sys *sys)
{
	t_env_var	*new_var;

	(void)sys;
	new_var = malloc(sizeof(t_env_var));
	if (!new_var)
		return (NULL);
	new_var->key = ft_strdup(key);
	if (value)
		new_var->value = ft_strdup(value);
	else
		new_var->value = NULL;
	new_var->exported = false;
	new_var->next = NULL;
	return (new_var);
}

void	update_env_var(t_env_var *env_var, char *value, t_sys *sys)
{
	(void)sys;
	if (!env_var)
		return ;
	if (env_var->value)
		free(env_var->value);
	if (value)
		env_var->value = ft_strdup(value);
	else
		env_var->value = NULL;
}

static void	remove_first_env_var(t_env_var **env_list, t_sys *sys)
{
	t_env_var	*current;

	(void)sys;
	current = *env_list;
	*env_list = current->next;
	free(current->key);
	if (current->value)
		free(current->value);
	free(current);
}

static void	remove_middle_env_var(t_env_var *prev, t_env_var *current,
			t_sys *sys)
{
	(void)sys;
	prev->next = current->next;
	free(current->key);
	if (current->value)
		free(current->value);
	free(current);
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
		remove_first_env_var(env_list, sys);
		return ;
	}
	prev = current;
	current = current->next;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			remove_middle_env_var(prev, current, sys);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	free_env_list_safe(t_env_var *env_list)
{
	t_env_var	*current;
	t_env_var	*next;

	current = env_list;
	while (current)
	{
		next = current->next;
		free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

void	free_env_list(t_env_var *env_list, t_sys *sys)
{
	(void)sys;
	free_env_list_safe(env_list);
}

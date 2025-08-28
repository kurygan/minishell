/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:32:14 by emetel            #+#    #+#             */
/*   Updated: 2025/08/28 18:00:58 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env_var	*create_env_var(char *key, char *value, t_sys *sys)
{
	t_env_var	*new_var;

	new_var = gc_malloc(&sys->env_gc, sizeof(t_env_var));
	if (!new_var)
		return (NULL);
	new_var->key = gc_strdup(key, &sys->env_gc);
	if (value)
		new_var->value = gc_strdup(value, &sys->env_gc);
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
		gc_free(env_var->value, &sys->env_gc);
	if (value)
		env_var->value = gc_strdup(value, &sys->env_gc);
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
		gc_free(current->key, &sys->env_gc);
		if (current->value)
			gc_free(current->value, &sys->env_gc);
		gc_free(current, &sys->env_gc);
		return ;
	}
	prev = current;
	current = current->next;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			prev->next = current->next;
			gc_free(current->key, &sys->env_gc);
			if (current->value)
				gc_free(current->value, &sys->env_gc);
			gc_free(current, &sys->env_gc);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

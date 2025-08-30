/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:32:14 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 16:04:38 by emetel           ###   ########.fr       */
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

static void	free_env_var_node(t_env_var *node, t_sys *sys)
{
	gc_free(node->key, &sys->env_gc);
	if (node->value)
		gc_free(node->value, &sys->env_gc);
	gc_free(node, &sys->env_gc);
}

static void	remove_first_node(t_env_var **env_list, t_sys *sys)
{
	t_env_var	*temp;

	temp = *env_list;
	*env_list = (*env_list)->next;
	free_env_var_node(temp, sys);
}

void	remove_env_var(t_env_var **env_list, char *key, t_sys *sys)
{
	t_env_var	*current;
	t_env_var	*prev;

	if (!*env_list || !key)
		return ;
	if (ft_strcmp((*env_list)->key, key) == 0)
	{
		remove_first_node(env_list, sys);
		return ;
	}
	prev = *env_list;
	current = (*env_list)->next;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			prev->next = current->next;
			free_env_var_node(current, sys);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:50:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 16:04:38 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	add_env_var_exported(t_env_var **env_list, char *key, char *value, \
			t_sys *sys)
{
	t_env_var	*new_var;
	t_env_var	*current;

	if (!key)
		return ;
	new_var = create_env_var(key, value, sys);
	if (!new_var)
		return ;
	new_var->exported = true;
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

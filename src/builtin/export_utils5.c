/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 16:05:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 16:04:38 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	add_or_append_var(t_env_var **env_list, char *key, char *value, \
			t_sys *sys)
{
	t_env_var	*existing_var;
	char		*new_value;

	existing_var = find_env_var(*env_list, key);
	if (existing_var && existing_var->value && value)
	{
		new_value = gc_strjoin(existing_var->value, value, &(sys->env_gc));
		update_env_var(existing_var, new_value, sys);
	}
	else if (existing_var)
	{
		update_env_var(existing_var, value, sys);
	}
	else
	{
		add_env_var_exported(env_list, key, value, sys);
	}
}

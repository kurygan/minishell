/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:45:00 by emetel            #+#    #+#             */
/*   Updated: 2025/09/06 14:14:02 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

char	*get_env_value_from_both_lists(char *var_name, t_sys *sys)
{
	char	*value;

	if (!var_name || !sys)
		return (NULL);
	value = get_env_value_from_list(var_name, sys->export_list);
	if (value)
		return (value);
	value = get_cd_pwd_var_value(sys->cd_pwd_vars, var_name);
	if (value)
		return (value);
	return (NULL);
}

char	*get_env_value_for_expansion(char *var_name, t_sys *sys)
{
	if (!var_name || !sys)
		return (NULL);
	return (get_env_value_from_list(var_name, sys->export_list));
}

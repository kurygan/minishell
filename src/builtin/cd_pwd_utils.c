/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:00:00 by emetel            #+#    #+#             */
/*   Updated: 2025/09/06 15:22:08 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_cd_pwd_var(t_env_var **cd_pwd_vars, char *key, char *value, \
			t_sys *sys)
{
	t_env_var	*new_var;
	t_env_var	*current;

	new_var = create_env_var(key, value, sys);
	if (!new_var)
		return ;
	new_var->exported = true;
	if (!*cd_pwd_vars)
	{
		*cd_pwd_vars = new_var;
		return ;
	}
	current = *cd_pwd_vars;
	while (current->next)
		current = current->next;
	current->next = new_var;
}

void	update_cd_pwd_var(t_env_var *cd_pwd_var, char *value, t_sys *sys)
{
	if (!cd_pwd_var)
		return ;
	if (cd_pwd_var->value)
		gc_free(cd_pwd_var->value, &sys->env_gc);
	if (value)
		cd_pwd_var->value = gc_strdup(value, &sys->env_gc);
	else
		cd_pwd_var->value = NULL;
}

t_env_var	*find_cd_pwd_var(t_env_var *cd_pwd_vars, char *key)
{
	t_env_var	*current;

	if (!cd_pwd_vars || !key)
		return (NULL);
	current = cd_pwd_vars;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

char	*get_cd_pwd_var_value(t_env_var *cd_pwd_vars, char *key)
{
	t_env_var	*var;

	var = find_cd_pwd_var(cd_pwd_vars, key);
	if (var)
		return (var->value);
	return (NULL);
}

void	free_cd_pwd_vars(t_env_var *cd_pwd_vars, t_sys *sys)
{
	t_env_var	*current;
	t_env_var	*next;

	current = cd_pwd_vars;
	while (current)
	{
		next = current->next;
		gc_free(current->key, &sys->env_gc);
		if (current->value)
			gc_free(current->value, &sys->env_gc);
		gc_free(current, &sys->env_gc);
		current = next;
	}
}

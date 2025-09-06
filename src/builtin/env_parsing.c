/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:55:00 by emetel            #+#    #+#             */
/*   Updated: 2025/09/06 15:22:08 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env_var	*parse_env_string(char *env_str, t_sys *sys)
{
	char		*equal_pos;
	char		*key;
	char		*value;
	t_env_var	*env_var;

	(void)sys;
	if (!env_str)
		return (NULL);
	equal_pos = ft_strchr(env_str, '=');
	if (!equal_pos)
		return (NULL);
	key = gc_substr(env_str, 0, equal_pos - env_str, &sys->env_gc);
	value = gc_strdup(equal_pos + 1, &sys->env_gc);
	env_var = create_env_var(key, value, sys);
	if (ft_strcmp(key, "_") != 0)
		env_var->exported = true;
	return (env_var);
}

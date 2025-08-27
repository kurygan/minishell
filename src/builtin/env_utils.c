/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:55:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/25 14:25:20 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	key = gc_substr(env_str, 0, equal_pos - env_str, &(sys->garbage));
	value = gc_strdup(equal_pos + 1, &sys->garbage);
	env_var = create_env_var(key, value, sys);
	return (env_var);
}

static t_env_var	*init_default_env(t_sys *sys)
{
	t_env_var	*head;
	char		cwd[4096];

	head = create_env_var("PWD", getcwd(cwd, sizeof(cwd)), sys);
	if (!head)
		return (NULL);
	add_env_var(&head, "SHLVL", "1", sys);
	add_env_var(&head, "_", "/usr/bin/env", sys);
	add_env_var(&head, "PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", sys);
	return (head);
}

static t_env_var	*init_from_env_array(char **env, t_sys *sys)
{
	t_env_var	*head;
	t_env_var	*current;
	int			i;

	head = parse_env_string(env[0], sys);
	if (!head)
		return (NULL);
	current = head;
	i = 1;
	while (env[i])
	{
		current->next = parse_env_string(env[i], sys);
		current = current->next;
		i++;
	}
	return (head);
}

t_env_var	*init_env_list(char **env, t_sys *sys)
{
	if (!env || !env[0])
		return (init_default_env(sys));
	return (init_from_env_array(env, sys));
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

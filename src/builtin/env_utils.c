/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:55:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/28 17:55:41 by mkettab          ###   ########.fr       */
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
	key = gc_substr(env_str, 0, ft_strlen(env_str) - ft_strlen(equal_pos), &sys->env_gc);
	value = gc_strdup(equal_pos + 1, &sys->env_gc);
	env_var = create_env_var(key, value, sys);
	if (ft_strcmp(key, "_") != 0)
		env_var->exported = true;
	return (env_var);
}

static t_env_var	*init_default_env(t_sys *sys)
{
	t_env_var	*head;
	char		cwd[4096];

	head = create_env_var("PWD", getcwd(cwd, sizeof(cwd)), sys);
	if (!head)
		return (NULL);
	head->exported = true;
	add_env_var_exported(&head, "SHLVL", "1", sys);
	add_env_var(&head, "_", "/usr/bin/env", sys);
	add_env_var_exported(&head, "PATH", \
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
	t_env_var	*env_list;

	if (!env || !env[0])
		env_list = init_default_env(sys);
	else
		env_list = init_from_env_array(env, sys);
	if (env_list)
		increment_shlvl(env_list, sys);
	return (env_list);
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
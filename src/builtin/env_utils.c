/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:55:00 by emetel            #+#    #+#             */
/*   Updated: 2025/09/06 15:22:08 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static void	add_parsed_var_to_list(t_env_var **head, t_env_var **current, \
		t_env_var *parsed_var)
{
	if (!*head)
	{
		*head = parsed_var;
		*current = *head;
	}
	else
	{
		(*current)->next = parsed_var;
		*current = (*current)->next;
	}
}

static void	cleanup_oldpwd_var(t_env_var *parsed_var, t_sys *sys)
{
	gc_free(parsed_var->key, &sys->env_gc);
	if (parsed_var->value)
		gc_free(parsed_var->value, &sys->env_gc);
	gc_free(parsed_var, &sys->env_gc);
}

static t_env_var	*init_from_env_array(char **env, t_sys *sys)
{
	t_env_var	*head;
	t_env_var	*current;
	int			i;
	t_env_var	*parsed_var;

	head = NULL;
	i = 0;
	while (env[i])
	{
		parsed_var = parse_env_string(env[i], sys);
		if (parsed_var)
		{
			if (ft_strcmp(parsed_var->key, "OLDPWD") != 0)
				add_parsed_var_to_list(&head, &current, parsed_var);
			else
				cleanup_oldpwd_var(parsed_var, sys);
		}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:15:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/28 14:37:02 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_env(t_cmd_segment *cmd)
{
	t_env_var	*current;

	if (!cmd->sys->env_list)
		return ;
	current = cmd->sys->env_list;
	while (current)
	{
		if (current->value)
		{
			if (!(cmd->sys->env_was_empty && \
				ft_strcmp(current->key, "PATH") == 0))
			{
				ft_putstr_fd(current->key, 1);
				ft_putchar_fd('=', 1);
				ft_putendl_fd(current->value, 1);
			}
		}
		current = current->next;
	}
}

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

char	**env_list_to_array(t_env_var *env_list, t_sys *sys)
{
	char		**env_array;
	t_env_var	*current;
	int			count;
	int			i;

	count = 0;
	current = env_list;
	while (current)
	{
		if (current->exported)
			count++;
		current = current->next;
	}
	env_array = gc_malloc(&sys->garbage, sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		if (current->exported && current->value)
		{
			env_array[i] = gc_strjoin(gc_strjoin(current->key, "=", \
				&sys->garbage), current->value, &sys->garbage);
			i++;
		}
		else if (current->exported)
		{
			env_array[i] = gc_strdup(current->key, &sys->garbage);
			i++;
		}
		current = current->next;
	}
	env_array[i] = NULL;
	return (env_array);
}



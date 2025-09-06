/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:15:00 by emetel            #+#    #+#             */
/*   Updated: 2025/09/06 14:06:26 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_env(t_cmd_segment *cmd)
{
	t_env_var	*current;

	if (!cmd->sys->export_list)
		return ;
	current = cmd->sys->export_list;
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

static int	count_exported_vars_local(t_env_var *env_list)
{
	t_env_var	*current;
	int			count;

	count = 0;
	current = env_list;
	while (current)
	{
		if (current->exported)
			count++;
		current = current->next;
	}
	return (count);
}

static void	fill_env_array(char **env_array, t_env_var *env_list, t_sys *sys)
{
	t_env_var	*current;
	int			i;

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
}

char	**env_list_to_array(t_env_var *env_list, t_sys *sys)
{
	char		**env_array;
	int			count;

	count = count_exported_vars_local(env_list);
	env_array = gc_malloc(&sys->garbage, sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	fill_env_array(env_array, env_list, sys);
	return (env_array);
}

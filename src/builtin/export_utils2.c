/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:30:31 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/30 14:31:34 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_env_var	*create_temp_env_var(t_env_var *current, t_sys *sys)
{
	t_env_var	*temp;

	temp = gc_malloc(&sys->garbage, sizeof(t_env_var));
	temp->key = gc_strdup(current->key, &sys->garbage);
	if (current->value)
		temp->value = gc_strdup(current->value, &sys->garbage);
	else
		temp->value = NULL;
	temp->exported = current->exported;
	temp->next = NULL;
	return (temp);
}

static void	fill_array_with_exported_vars(t_env_var **array,
	t_env_var *env_list, t_sys *sys)
{
	t_env_var	*current;
	int			i;

	current = env_list;
	i = 0;
	while (current)
	{
		if (current->exported)
		{
			array[i] = create_temp_env_var(current, sys);
			i++;
		}
		current = current->next;
	}
}

void	print_export_list(t_env_var *env_list, t_sys *sys)
{
	t_env_var	**array;
	int			count;

	count = count_exported_vars(env_list);
	if (count == 0)
		return ;
	array = gc_malloc(&sys->garbage, sizeof(t_env_var *) * count);
	fill_array_with_exported_vars(array, env_list, sys);
	sort_env_array(array, count);
	print_sorted_export_list(array, count);
}

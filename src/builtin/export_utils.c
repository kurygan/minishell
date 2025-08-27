/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:55:06 by emetel            #+#    #+#             */
/*   Updated: 2025/08/27 13:37:15 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	count_exported_vars(t_env_var *env_list)
{
	int			count;
	t_env_var	*current;

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

static void	sort_env_array(t_env_var **array, int size)
{
	int			i;
	int			j;
	t_env_var	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (ft_strcmp(array[j]->key, array[j + 1]->key) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	fill_export_array(t_env_var *env_list, t_env_var **array)
{
	t_env_var	*current;
	int			i;

	current = env_list;
	i = 0;
	while (current)
	{
		if (current->exported)
		{
			array[i] = current;
			i++;
		}
		current = current->next;
	}
}

static void	print_sorted_export_list(t_env_var **array, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(array[j]->key, 1);
		if (array[j]->value)
		{
			ft_putchar_fd('=', 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(array[j]->value, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		j++;
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
	fill_export_array(env_list, array);
	sort_env_array(array, count);
	print_sorted_export_list(array, count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:34:17 by emetel            #+#    #+#             */
/*   Updated: 2025/09/06 15:02:34 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_shlvl_warning(int level)
{
	ft_putstr_fd("minishell: warning: shell level (", 2);
	ft_putint_fd(level, 2);
	ft_putstr_fd(") too high, resetting to 1\n", 2);
}

void	increment_shlvl(t_env_var *env_list, t_sys *sys)
{
	t_env_var	*shlvl_var;
	int			current_level;
	char		*new_level_str;

	(void)sys;
	shlvl_var = find_env_var(env_list, "SHLVL");
	if (shlvl_var && shlvl_var->value)
	{
		current_level = ft_atoi(shlvl_var->value);
		if (current_level >= 999)
		{
			print_shlvl_warning(current_level + 1);
			current_level = 1;
		}
		else
			current_level++;
		new_level_str = gc_itoa(current_level, &sys->env_gc);
		if (new_level_str)
			shlvl_var->value = new_level_str;
	}
}

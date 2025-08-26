/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:55:06 by emetel            #+#    #+#             */
/*   Updated: 2025/08/26 23:23:13 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	process_export_arg(char *arg, t_env_var **env_list, t_sys *sys, \
			bool *error_occurred)
{
	char	*key;
	char	*value;

	key = extract_key_value(arg, &value, sys);
	if (!is_valid_identifier(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		*error_occurred = true;
	}
	else
	{
		add_or_update_var(env_list, key, value, sys);
	}
}

void	exec_export(t_cmd_segment *cmd)
{
	int		i;
	bool	error_occurred;

	if (!cmd->args || !cmd->args[0])
	{
		print_export_list(cmd->sys->env_list, cmd->sys);
		return ;
	}
	error_occurred = false;
	i = 0;
	while (cmd->args[i])
	{
		process_export_arg(cmd->args[i], &cmd->sys->env_list, cmd->sys, \
			&error_occurred);
		i++;
	}
	if (error_occurred)
		cmd->sys->exit_status = 1;
	else
		cmd->sys->exit_status = 0;
}

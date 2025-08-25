/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:00:00 by emetel            #+#    #+#             */
/*   Updated: 2025/01/27 10:00:00 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_cd(t_cmd_segment *cmd)
{
	char	*path;
	char	*home;
	char	*old_pwd;

	old_pwd = get_env_value_from_list("PWD", cmd->sys->env_list);
	if (!cmd->args || !cmd->args[0])
	{
		home = get_env_value_from_list("HOME", cmd->sys->env_list);
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			cmd->sys->exit_status = 1;
			return ;
		}
		if (!change_directory(home, cmd))
			return ;
	}
	else
	{
		path = cmd->args[0];
		if (!change_directory(path, cmd))
			return ;
	}
	update_pwd_variables(cmd, old_pwd);
	cmd->sys->exit_status = 0;
}

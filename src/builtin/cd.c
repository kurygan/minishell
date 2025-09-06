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

static void	handle_cd_home(t_cmd_segment *cmd)
{
	char	*home;
	char	*old_pwd;

	home = get_env_value_from_list("HOME", cmd->sys->export_list);
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		cmd->sys->exit_status = 1;
		return ;
	}
	old_pwd = get_cd_pwd_var_value(cmd->sys->cd_pwd_vars, "PWD");
	if (change_directory(home, cmd))
		update_pwd_variables(cmd, old_pwd);
}

static void	handle_cd_oldpwd(t_cmd_segment *cmd)
{
	char	*oldpwd;

	oldpwd = get_cd_pwd_var_value(cmd->sys->cd_pwd_vars, "OLDPWD");
	if (!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		cmd->sys->exit_status = 1;
		return ;
	}
	if (change_directory(oldpwd, cmd))
	{
		ft_putendl_fd(oldpwd, 1);
		update_pwd_variables(cmd, NULL);
	}
}

static void	handle_cd_path(t_cmd_segment *cmd, char *path)
{
	char	*old_pwd;

	old_pwd = get_cd_pwd_var_value(cmd->sys->cd_pwd_vars, "PWD");
	if (change_directory(path, cmd))
		update_pwd_variables(cmd, old_pwd);
}

void	exec_cd(t_cmd_segment *cmd)
{
	if (!cmd->args || !cmd->args[0])
		handle_cd_home(cmd);
	else if (cmd->args[0][0] == '\0')
	{
		cmd->sys->exit_status = 0;
	}
	else if (ft_strcmp(cmd->args[0], "-") == 0)
		handle_cd_oldpwd(cmd);
	else
		handle_cd_path(cmd, cmd->args[0]);
}

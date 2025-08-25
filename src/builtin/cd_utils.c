/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:45:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/25 14:56:04 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	update_pwd_variables(t_cmd_segment *cmd, char *old_pwd)
{
	char		*new_pwd;
	char		cwd[4096];
	t_env_var	*pwd_var;
	t_env_var	*old_pwd_var;

	new_pwd = getcwd(cwd, sizeof(cwd));
	if (!new_pwd)
		return ;
	if (old_pwd)
	{
		old_pwd_var = find_env_var(cmd->sys->env_list, "OLDPWD");
		if (old_pwd_var)
			update_env_var(old_pwd_var, old_pwd, cmd->sys);
		else
			add_env_var(&cmd->sys->env_list, "OLDPWD", old_pwd, cmd->sys);
	}
	pwd_var = find_env_var(cmd->sys->env_list, "PWD");
	if (pwd_var)
		update_env_var(pwd_var, new_pwd, cmd->sys);
	else
		add_env_var(&cmd->sys->env_list, "PWD", new_pwd, cmd->sys);
}

void	handle_cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	if (errno == ENOENT)
		ft_putstr_fd("No such file or directory\n", 2);
	else if (errno == EACCES)
		ft_putstr_fd("Permission denied\n", 2);
	else if (errno == ENOTDIR)
		ft_putstr_fd("Not a directory\n", 2);
	else
		ft_putstr_fd("Directory error\n", 2);
}

int	change_directory(char *path, t_cmd_segment *cmd)
{
	if (chdir(path) == -1)
	{
		handle_cd_error(path);
		cmd->sys->exit_status = 1;
		return (0);
	}
	return (1);
}

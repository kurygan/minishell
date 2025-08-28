/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:45:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/28 21:03:44 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_cd_error(char *path, char *error_msg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error_msg, 2);
}

static void	handle_cd_error(char *path)
{
	if (errno == ENOENT)
		print_cd_error(path, "No such file or directory");
	else if (errno == EACCES)
		print_cd_error(path, "Permission denied");
	else if (errno == ENOTDIR)
		print_cd_error(path, "Not a directory");
	else if (errno == ELOOP)
		print_cd_error(path, "Too many levels of symbolic links");
	else if (errno == ENAMETOOLONG)
		print_cd_error(path, "File name too long");
	else
		print_cd_error(path, "Directory error");
}

int	change_directory(char *path, t_cmd_segment *cmd)
{
	if (!path)
		return (0);
	if (chdir(path) == -1)
	{
		handle_cd_error(path);
		cmd->sys->exit_status = 1;
		return (0);
	}
	cmd->sys->exit_status = 0;
	return (1);
}

static char	*get_current_working_directory(t_sys *sys)
{
	char	cwd[4096];

	if (!getcwd(cwd, sizeof(cwd)))
		return (NULL);
	return (gc_strdup(cwd, &sys->env_gc));
}

void	update_pwd_variables(t_cmd_segment *cmd, char *old_pwd)
{
	char		*new_pwd;
	t_env_var	*pwd_var;
	t_env_var	*old_pwd_var;

	new_pwd = get_current_working_directory(cmd->sys);
	if (!new_pwd)
		return ;
	if (old_pwd)
	{
		old_pwd_var = find_env_var(cmd->sys->env_list, "OLDPWD");
		if (old_pwd_var)
			update_env_var(old_pwd_var, old_pwd, cmd->sys);
		else
			add_env_var_exported(&cmd->sys->env_list, "OLDPWD", old_pwd, \
				cmd->sys);
	}
	pwd_var = find_env_var(cmd->sys->env_list, "PWD");
	if (pwd_var)
		update_env_var(pwd_var, new_pwd, cmd->sys);
	else
		add_env_var_exported(&cmd->sys->env_list, "PWD", new_pwd, cmd->sys);
}

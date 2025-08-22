/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 01:46:05 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/22 12:18:50 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_builtin(char	*cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") \
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") \
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") \
		|| !ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}

void	exec_pwd(t_cmd_segment *cmd)
{
	char	*cwd;

	(void)cmd;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("pwd");
		return ;
	}
	ft_putendl_fd(cwd, 1);
	free(cwd);
}

void	exec_cd(t_cmd_segment *cmd)
{
	char	*path;
	char	*home;

	if (!cmd->args || !cmd->args[0])
	{
		home = get_env_value("HOME", cmd->sys->env);
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			cmd->sys->exit_status = 1;
			return ;
		}
		if (chdir(home) == -1)
		{
			perror("cd");
			cmd->sys->exit_status = 1;
			return ;
		}
	}
	else
	{
		path = cmd->args[0];
		if (chdir(path) == -1)
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
			cmd->sys->exit_status = 1;
			return ;
		}
	}
	cmd->sys->exit_status = 0;
}

void	exec_builtin(t_cmd_segment *cmd)
{
	if (!(ft_strcmp(cmd->cmd, "echo")))
		exec_echo(cmd);
	else if (!(ft_strcmp(cmd->cmd, "pwd")))
		exec_pwd(cmd);
	else if (!(ft_strcmp(cmd->cmd, "cd")))
		exec_cd(cmd);
}

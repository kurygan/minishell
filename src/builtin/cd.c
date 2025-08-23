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

	if (!cmd->args || !cmd->args[0])
	{
		home = get_env_value_from_list("HOME", cmd->sys->env_list);
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

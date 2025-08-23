/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 01:46:05 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/23 23:11:56 by emetel           ###   ########.fr       */
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

void	exec_builtin(t_cmd_segment *cmd)
{
	if (!(ft_strcmp(cmd->cmd, "echo")))
		exec_echo(cmd);
	else if (!(ft_strcmp(cmd->cmd, "pwd")))
		exec_pwd(cmd);
	else if (!(ft_strcmp(cmd->cmd, "cd")))
		exec_cd(cmd);
}

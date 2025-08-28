/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:30:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/28 22:05:37 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	is_numeric(char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!str[i])
		return (false);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	handle_numeric_error(t_cmd_segment *cmd, char *arg)
{
	ft_printf("exit: %s: numeric argument required\n", arg);
	cmd->sys->exit_status = 255;
	exit(cmd->sys->exit_status);
}

void	exec_exit(t_cmd_segment *cmd)
{
	long long	exit_code;
	bool		error;

	if (!cmd->args || !cmd->args[0])
		exit(cmd->sys->exit_status);
	if (!is_numeric(cmd->args[0]))
		handle_numeric_error(cmd, cmd->args[0]);
	if (cmd->args[1])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		cmd->sys->exit_status = 1;
		exit(cmd->sys->exit_status);
	}
	error = false;
	exit_code = ft_atoll(cmd->args[0], &error);
	if (error)
		handle_numeric_error(cmd, cmd->args[0]);
	cmd->sys->exit_status = (int)(exit_code & 0xFF);
	exit(cmd->sys->exit_status);
}

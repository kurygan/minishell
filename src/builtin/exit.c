/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:30:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/29 20:33:53 by emetel           ###   ########.fr       */
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
	cmd->sys->exit_status = 2;
	exit(cmd->sys->exit_status);
}

void	exec_exit(t_cmd_segment *cmd)
{
	long long	exit_code;
	bool		error;
	int			arg_index;

	// ft_putendl_fd("exit", 2);
	if (!cmd->args || !cmd->args[0])
		exit(cmd->sys->exit_status);
	arg_index = 0;
	if (ft_strcmp(cmd->args[arg_index], "--") == 0)
		arg_index++;
	if (!cmd->args[arg_index])
		exit(cmd->sys->exit_status);
	if (!is_numeric(cmd->args[arg_index]))
		handle_numeric_error(cmd, cmd->args[arg_index]);
	if (cmd->args[arg_index + 1])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		cmd->sys->exit_status = 1;
		return ;
	}
	error = false;
	exit_code = ft_atoll(cmd->args[arg_index], &error);
	if (error)
		handle_numeric_error(cmd, cmd->args[arg_index]);
	cmd->sys->exit_status = (int)(exit_code & 0xFF);
	exit(cmd->sys->exit_status);
}

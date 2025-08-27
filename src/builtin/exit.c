/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:30:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/27 15:30:45 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	is_numeric(char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	i = 0;
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

static long long	ft_atoll(char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	exec_exit(t_cmd_segment *cmd)
{
	long long	exit_code;

	ft_putendl_fd("exit", 2);
	if (!cmd->args || !cmd->args[1])
	{
		cmd->sys->exit_status = 0;
		exit(0);
	}
	if (!is_numeric(cmd->args[1]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		cmd->sys->exit_status = 255;
		exit(255);
	}
	exit_code = ft_atoll(cmd->args[1]);
	if (cmd->args[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		cmd->sys->exit_status = 1;
		return ;
	}
	cmd->sys->exit_status = (int)(exit_code & 0xFF);
	exit(cmd->sys->exit_status);
}

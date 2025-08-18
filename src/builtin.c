/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 01:46:05 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/18 01:20:11 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_builtin(char	*cmd)
{
	if (!ft_strcmp(cmd, "echo") \
			|| !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") \
			|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset") \
			|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}

static bool	is_n_option(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (false);
	i = 1;
	while (str[i] && str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

void	exec_echo(t_cmd_segment *cmd)
{
	char	**args;
	bool	print;
	bool	no_newline;

	if (!cmd->args)
		return ((void)ft_putstr_fd("\n", 1));
	args = cmd->args;
	no_newline = false;
	print = false;
	while (*args && is_n_option(*args))
	{
		no_newline = true;
		args++;
	}
	while (*args)
	{
		if (print)
			ft_putstr_fd(" ", 1);
		print = true;
		ft_putstr_fd(*args, 1);
		args++;
	}
	if (!no_newline)
		ft_putstr_fd("\n", 1);
}

void	exec_builtin(t_cmd_segment *cmd)
{
	if (!(ft_strcmp(cmd->cmd, "echo")))
		exec_echo(cmd);
}

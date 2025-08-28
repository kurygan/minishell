/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:23:38 by emetel            #+#    #+#             */
/*   Updated: 2025/08/27 15:39:20 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	process_unset_arg(char *arg, t_cmd_segment *cmd)
{
	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("unset: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (false);
	}
	remove_env_var(&cmd->sys->env_list, arg, cmd->sys);
	return (true);
}

void	exec_unset(t_cmd_segment *cmd)
{
	int		i;
	bool	error_occurred;

	if (!cmd->args || !cmd->args[0])
		return ;
	error_occurred = false;
	i = 0;
	while (cmd->args[i])
	{
		if (!process_unset_arg(cmd->args[i], cmd))
			error_occurred = true;
		i++;
	}
	if (error_occurred)
		cmd->sys->exit_status = 1;
	else
		cmd->sys->exit_status = 0;
}

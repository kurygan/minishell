/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:00:00 by emetel            #+#    #+#             */
/*   Updated: 2025/01/27 10:00:00 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_pwd(t_cmd_segment *cmd)
{
	char	*pwd;

	pwd = get_env_value_from_list("PWD", cmd->sys->env_list);
	if (!pwd)
	{
		ft_putstr_fd("minishell: pwd: PWD not set\n", 2);
		cmd->sys->exit_status = 1;
		return ;
	}
	ft_putendl_fd(pwd, 1);
	cmd->sys->exit_status = 0;
}

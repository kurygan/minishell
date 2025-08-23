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

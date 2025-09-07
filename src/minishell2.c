/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:30:00 by emetel            #+#    #+#             */
/*   Updated: 2025/09/07 15:24:07 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_sys	*init_system(char **env)
{
	t_sys	*sys;

	sys = malloc(sizeof(t_sys));
	if (!sys)
		return (NULL);
	ft_memset(sys, 0, sizeof(t_sys));
	sys->exit_status = 0;
	sys->env = env;
	sys->env_was_empty = (!env || !env[0]);
	sys->garbage = NULL;
	sys->env_gc = NULL;
	sys->export_list = init_env_list(env, sys);
	sys->cd_pwd_vars = init_cd_pwd_vars(sys);
	return (sys);
}

void	close_all_fd(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

int	cleanup_and_exit(t_sys *sys, struct termios *orig_termios)
{
	int	exit_status;

	gc_carbonize(&(sys->env_gc));
	exit_status = sys->exit_status;
	close_all_fd();
	free(sys);
	reset_signals(orig_termios);
	clear_history();
	return (exit_status);
}

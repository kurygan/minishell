/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 03:15:09 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/14 19:08:14 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char*	get_path(char *cmd, t_sys *sys)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (gc_strdup(cmd, &(sys->garbage)));
	path_env = NULL;
	i = -1;
	while (sys->env && (sys->env)[++i])
	{
		if (!ft_strncmp(sys->env[i], "PATH=", 5))
		{
			path_env = sys->env[i] + 5;
			break ;
		}
	}
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	i = -1;
	while (paths && paths[++i])
	{
		full_path = gc_strjoin(paths[i], "/", &(sys->garbage));
		full_path = gc_strjoin(full_path, cmd, &(sys->garbage));
		if (!(access(full_path, X_OK)))
			return (ft_freetab(paths), full_path);
	}
	return (ft_freetab(paths), gc_strdup(cmd, &(sys->garbage)));
}

void	exec(t_sys *sys)
{
	pid_t		pid;
	int			status;
	char		*cmd;
	static char	*default_args[2];

	if (!sys->command || !sys->command->cmd)
		return ;
	if (is_builtin(sys->command->cmd))
		return (exec_builtin(sys->command));
	cmd = get_path(sys->command->cmd, sys);
	default_args[0] = cmd;
	default_args[1] = NULL;
	pid = fork();
	if (pid == 0)
	{
		execve(cmd, default_args, sys->env);
		perror("minishell");
		exit(127);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			sys->exit_status = WEXITSTATUS(status);
		else
			sys->exit_status = 1;
	}
	else
	{
		perror("minishell");
		sys->exit_status = 1;
	}
}

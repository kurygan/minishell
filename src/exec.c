/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 03:15:09 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/18 02:25:18 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_path(char *cmd, t_sys *sys)
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

void fd_redir(t_sys *sys, int fd[2])
{
	fd[0] = -1;
	fd[1] = -1;
	if (sys->command->heredoc || sys->command->infile)
	{
		fd[0] = handle_redir_in(sys->command, sys);
		if (sys->command->infile)
			printf("Infile FD: %d\n", fd[0]);
		if (fd[0] == -1)
		{
			sys->exit_status = 1;
			return ;
		}
	}
	if (sys->command->outfile)
	{
		fd[1] = handle_redir_out(sys->command);
		printf("Outfile FD: %d\n", fd[1]);
		if (fd[1] == -1)
		{
			ft_putendl_fd("outfile", 2);
			sys->exit_status = 1;
			return ;
		}
	}
}

char	**get_args(t_cmd_segment *command)
{
	char	**args;
	char	**temp;
	int		arg_count;
	int		i;

	arg_count = 0;
	i = 0;
	if (command->args)
	{
		temp = command->args;
		while (temp[arg_count])
			arg_count++;
	}
	if (arg_count == 0)
	{
		args = gc_malloc(&(command->sys->garbage), sizeof(char *) * 2);
		args[0] = command->cmd;
		args[1] = NULL;
	}
	else
	{
		args = gc_malloc(&(command->sys->garbage), \
			sizeof(char *) * (arg_count + 2));
		args[i++] = command->cmd;
		while (i <= arg_count && temp[i - 1])
		{
			args[i] = temp[i - 1];
			i++;
		}
		args[i] = NULL;
	}
	return (args);
}

void	exec(t_sys *sys)
{
	pid_t		pid;
	int			status;
	char		*cmd;
	char		**args;
	int			fd[2];

	if (!sys->command || !sys->command->cmd)
		return ;
	fd_redir(sys, fd);
	cmd = get_path(sys->command->cmd, sys);
	args = get_args(sys->command);
	pid = fork();
	if (pid == 0)
	{
		if (fd[0] != -1)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
		if (fd[1] != -1)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		if (is_builtin(sys->command->cmd))
		{
			exec_builtin(sys->command);
			exit(0);
		}
		else
		{
			execve(cmd, args, sys->env);
			perror("minishell");
			exit(127);
		}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 03:15:09 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/18 06:37:34 by emetel           ###   ########.fr       */
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

void	fd_redir(t_cmd_segment *command, int fd[2])
{
	fd[0] = -1;
	fd[1] = -1;
	if (command->heredoc || command->infile)
	{
		fd[0] = handle_redir_in(command, command->sys);
		if (command->infile)
			printf("Infile FD: %d\n", fd[0]);
		if (fd[0] == -1)
		{
			command->sys->exit_status = 1;
			return ;
		}
	}
	if (command->outfile)
	{
		fd[1] = handle_redir_out(command);
		printf("Outfile FD: %d\n", fd[1]);
		if (fd[1] == -1)
		{
			ft_putendl_fd("outfile", 2);
			command->sys->exit_status = 1;
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

int	**create_pipes(int pipe_count, t_sys *sys)
{
	int	**pipes;
	int	i;

	pipes = gc_malloc(&(sys->garbage), sizeof(int *) * pipe_count);
	i = 0;
	while (i < pipe_count)
	{
		pipes[i] = gc_malloc(&(sys->garbage), sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	close_all_pipes(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	count_commands(t_cmd_segment *segments)
{
	int	count;

	count = 0;
	while (segments)
	{
		count++;
		segments = segments->next;
	}
	return (count);
}

void	wait_for_children(pid_t *pids, int cmd_count, t_sys *sys)
{
	int	i;
	int	status;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1) // Last command determines exit status
		{
			if (WIFEXITED(status))
				sys->exit_status = WEXITSTATUS(status);
			else
				sys->exit_status = 1;
		}
		i++;
	}
}

void	exec_child_process(t_cmd_segment *cmd, int **pipes, int cmd_index, \
			int total_cmds)
{
	int		temp_pipe[2];
	char	*path;
	char	**args;

	if (pipes)
	{
		if (cmd_index > 0) // Not first command
		{
			dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
		}
		if (cmd_index < total_cmds - 1) // Not last command
		{
			dup2(pipes[cmd_index][1], STDOUT_FILENO);
		}
		close_all_pipes(pipes, total_cmds - 1);
		fd_redir(cmd, pipes[cmd_index]);
	}
	else
		fd_redir(cmd, temp_pipe);
	// Execute command
	if (is_builtin(cmd->cmd))
	{
		exec_builtin(cmd);
		exit(0);
	}
	else
	{
		path = get_path(cmd->cmd, cmd->sys);
		args = get_args(cmd);
		execve(path, args, cmd->sys->env);
		perror("minishell");
		exit(127);
	}
}

void	exec_pipeline(t_cmd_segment *segments, t_sys *sys)
{
	t_cmd_segment	*current;
	int				cmd_count;
	int				**pipes;
	pid_t			*pids;
	int				i;

	cmd_count = count_commands(segments);
	current = segments;
	if (cmd_count == 1)
	{
		exec_child_process(current, NULL, 1, 1);
		return ;
	}
	pipes = create_pipes(cmd_count - 1, sys);
	pids = gc_malloc(&(sys->garbage), sizeof(pid_t) * cmd_count);
	i = 0;
	while (current)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			exec_child_process(current, pipes, i, cmd_count);
		current = current->next;
		i++;
	}
	close_all_pipes(pipes, cmd_count - 1);
	wait_for_children(pids, cmd_count, sys);
}

// Replace your current exec function with this:
void	exec(t_sys *sys)
{
	if (!sys->command || !sys->command->cmd)
		return ;
	exec_pipeline(sys->command, sys);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:30:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/25 14:35:33 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_path(char *cmd, t_sys *sys)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (gc_strdup(cmd, &(sys->garbage)));
	path_env = get_env_value_from_list("PATH", sys->env_list);
	if (!path_env)
		return (gc_strdup(cmd, &(sys->garbage)));
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

void	fd_redir(t_cmd_segment *cmd, int cmd_index, int total_cmds, int **pipes)
{
	int	fd[2];

	if (cmd->infile || cmd->heredoc)
	{
		fd[0] = handle_redir_in(cmd, cmd->sys);
		if (fd[0] != -1)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
	}
	else if (cmd_index > 0 && pipes)
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	if (cmd->outfile)
	{
		fd[1] = handle_redir_out(cmd);
		if (fd[1] != -1)
		{
			dup2(fd[1], STDOUT_FILENO);
			close (fd[1]);
		}
	}
	else if (cmd_index < total_cmds - 1 && pipes)
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
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

	if (pipe_count == 0)
		return (NULL);
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
		if (pipes[i][0] > 0)
			close(pipes[i][0]);
		if (pipes[i][1] > 0)
			close(pipes[i][1]);
		i++;
	}
}

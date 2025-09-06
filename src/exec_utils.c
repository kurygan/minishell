/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:30:00 by emetel            #+#    #+#             */
/*   Updated: 2025/09/06 14:06:26 by emetel           ###   ########.fr       */
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
	path_env = get_env_value_from_both_lists("PATH", sys);
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

static void	handle_input_redir(t_cmd_segment *cmd, int cmd_index, int **pipes)
{
	int	fd;

	if (cmd->infile || cmd->heredoc)
	{
		fd = handle_redir_in(cmd, cmd->sys);
		if (fd != -1)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else
			exit(1);
	}
	else if (cmd_index > 0 && pipes)
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
}

static void	handle_output_redir(t_cmd_segment *cmd, int cmd_index, \
	int total_cmds, int **pipes)
{
	int	fd;

	if (cmd->outfiles)
	{
		fd = handle_redir_out(cmd);
		if (fd != -1)
		{
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else
			exit(1);
	}
	else if (cmd_index < total_cmds - 1 && pipes)
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
}

void	fd_redir(t_cmd_segment *cmd, int cmd_index, int total_cmds, int **pipes)
{
	handle_input_redir(cmd, cmd_index, pipes);
	handle_output_redir(cmd, cmd_index, total_cmds, pipes);
}

char	**get_args(t_cmd_segment *command)
{
	char	**args;
	int		arg_count;

	arg_count = count_args(command->args);
	if (arg_count == 0)
	{
		args = gc_malloc(&(command->sys->garbage), sizeof(char *) * 2);
		args[0] = command->cmd;
		args[1] = NULL;
	}
	else
		args = build_args_array(command, arg_count);
	return (args);
}

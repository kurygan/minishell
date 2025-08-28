/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 03:15:09 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/28 17:53:56 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_commands(t_cmd_segment *segments)
{
	int				count;
	t_cmd_segment	*tmp;

	count = 0;
	tmp = segments;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	wait_pid(pid_t pid, t_sys *sys, int i, int total)
{
	int	status;

	waitpid(pid, &status, 0);
	if (total == 0 || i == total)
		sys->exit_status = WEXITSTATUS(status);
}

void	exec_child_process(t_cmd_segment *cmd, int **pipes, int cmd_index, \
			int total_cmds)
{
	char	*path;
	char	**args;
	char	**env_array;

	fd_redir(cmd, cmd_index, total_cmds, pipes);
	if (pipes)
		close_all_pipes(pipes, total_cmds - 1);
	if (is_builtin(cmd->cmd))
	{
		exec_builtin(cmd);
		exit(0);
	}
	else
	{
		path = get_path(cmd->cmd, cmd->sys);
		args = get_args(cmd);
		env_array = env_list_to_array(cmd->sys->env_list, cmd->sys);
		if (execve(path, args, env_array))
		{
			ft_printf("%s: command not found\n", cmd->cmd);
			exit(127);
		}
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
	pipes = create_pipes(cmd_count - 1, sys);
	pids = gc_malloc(&(sys->garbage), sizeof(pid_t) * cmd_count);
	i = 0;
	while (current)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			exec_child_process(current, pipes, i, cmd_count);
		if (current->next && current->next->heredoc)
			wait_pid(pids[i], sys, i, cmd_count - 1);
		current = current->next;
		i++;
	}
	close_all_pipes(pipes, cmd_count - 1);
	i = 0;
	while (i < cmd_count)
	{
		wait_pid(pids[i], sys, i, cmd_count - 1);
		i++;
	}
}

void	exec(t_sys *sys)
{
	int	saved_stdfd[2];

	if (!sys->command || !sys->command->cmd)
		return ;
	if (count_commands(sys->command) == 1 && is_builtin(sys->command->cmd))
	{
		saved_stdfd[0] = dup(STDIN_FILENO);
		saved_stdfd[1] = dup(STDOUT_FILENO);
		fd_redir(sys->command, 0, 1, NULL);
		exec_builtin(sys->command);
		dup2(saved_stdfd[0], STDIN_FILENO);
		dup2(saved_stdfd[1], STDOUT_FILENO);
		close(saved_stdfd[0]);
		close(saved_stdfd[1]);
		return ;
	}
	exec_pipeline(sys->command, sys);
}

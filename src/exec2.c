/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:55:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 14:58:25 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	fork_and_exec_processes(t_cmd_segment *segments, int **pipes, \
	pid_t *pids, int cmd_count)
{
	t_cmd_segment	*current;
	int				i;

	current = segments;
	i = 0;
	while (current)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			exec_child_process(current, pipes, i, cmd_count);
		if (current->next && current->next->heredoc)
			wait_pid(pids[i], current->sys, i, cmd_count - 1);
		current = current->next;
		i++;
	}
}

static void	wait_for_all_processes(pid_t *pids, int cmd_count, t_sys *sys)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		wait_pid(pids[i], sys, i, cmd_count - 1);
		i++;
	}
}

void	exec_pipeline(t_cmd_segment *segments, t_sys *sys)
{
	int		cmd_count;
	int		**pipes;
	pid_t	*pids;

	cmd_count = count_commands(segments);
	pipes = create_pipes(cmd_count - 1, sys);
	pids = gc_malloc(&(sys->garbage), sizeof(pid_t) * cmd_count);
	fork_and_exec_processes(segments, pipes, pids, cmd_count);
	close_all_pipes(pipes, cmd_count - 1);
	wait_for_all_processes(pids, cmd_count, sys);
	setup_interactive_signals();
}

void	exec_single_builtin(t_cmd_segment *command)
{
	int	saved_stdfd[2];

	saved_stdfd[0] = dup(STDIN_FILENO);
	saved_stdfd[1] = dup(STDOUT_FILENO);
	fd_redir(command, 0, 1, NULL);
	exec_builtin(command);
	dup2(saved_stdfd[0], STDIN_FILENO);
	dup2(saved_stdfd[1], STDOUT_FILENO);
	close(saved_stdfd[0]);
	close(saved_stdfd[1]);
	setup_interactive_signals();
}

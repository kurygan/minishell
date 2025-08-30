/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 03:15:09 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/30 14:58:25 by emetel           ###   ########.fr       */
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
	int	sig;

	waitpid(pid, &status, 0);
	if (total == 0 || i == total)
	{
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT)
				sys->exit_status = 130;
			else if (sig == SIGQUIT)
			{
				sys->exit_status = 131;
				write(STDOUT_FILENO, "\n", 1);
			}
			else
				sys->exit_status = 128 + sig;
		}
		else
			sys->exit_status = WEXITSTATUS(status);
	}
}

static void	exec_external_command(t_cmd_segment *cmd)
{
	char	*path;
	char	**args;
	char	**env_array;

	if (!get_env_value_from_list("PATH", cmd->sys->env_list))
	{
		ft_printf("%s: No such file or directory\n", cmd->cmd);
		cmd->sys->exit_status = 127;
	}
	else
	{
		path = get_path(cmd->cmd, cmd->sys);
		args = get_args(cmd);
		env_array = env_list_to_array(cmd->sys->env_list, cmd->sys);
		if (execve(path, args, env_array))
		{
			ft_printf("%s: command not found\n", cmd->cmd);
			cmd->sys->exit_status = 127;
		}
	}
}

void	exec_child_process(t_cmd_segment *cmd, int **pipes, int cmd_index, \
			int total_cmds)
{
	setup_exec_signals();
	fd_redir(cmd, cmd_index, total_cmds, pipes);
	if (pipes)
		close_all_pipes(pipes, total_cmds - 1);
	if (cmd->cmd && cmd->cmd[0] != '\0' && is_builtin(cmd->cmd))
		exec_builtin(cmd);
	else if (cmd->cmd && cmd->cmd[0] != '\0')
		exec_external_command(cmd);
	exit(cmd->sys->exit_status);
}

void	exec(t_sys *sys)
{
	if (!sys->command)
		return ;
	if (count_commands(sys->command) == 1 && sys->command->cmd \
			&& sys->command->cmd[0] != '\0' && is_builtin(sys->command->cmd))
	{
		exec_single_builtin(sys->command);
		return ;
	}
	exec_pipeline(sys->command, sys);
}

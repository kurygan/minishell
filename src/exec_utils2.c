/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:50:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 14:58:25 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	count_args(char **args)
{
	int	count;

	count = 0;
	if (args)
	{
		while (args[count])
			count++;
	}
	return (count);
}

char	**build_args_array(t_cmd_segment *command, int arg_count)
{
	char	**args;
	int		i;

	args = gc_malloc(&(command->sys->garbage), \
		sizeof(char *) * (arg_count + 2));
	args[0] = command->cmd;
	i = 1;
	while (i <= arg_count && command->args[i - 1])
	{
		args[i] = command->args[i - 1];
		i++;
	}
	args[i] = NULL;
	return (args);
}

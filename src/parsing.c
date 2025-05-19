/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 03:51:04 by emetel            #+#    #+#             */
/*   Updated: 2025/05/20 00:52:53 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**split_line(char *line)
{
	char	**argv;

	argv = ft_split(line, ' ');
	if (!argv)
		exit(EXIT_FAILURE);
	return (argv);
}

static void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

static char	*find_executable(char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*full;
	int		i;

	path_env = getenv("PATH");
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full = ft_strjoin(paths[i], "/");
		full = ft_strjoin(full, cmd);
		if (access(full, X_OK) == 0)
		{
			free_argv(paths);
			return (full);
		}
		free(full);
		i++;
	}
	free_argv(paths);
	return (NULL);
}

void	handle_line(char *line, char **envp)
{
	char	**argv;
	pid_t	pid;
	char	*path;

	path = NULL;
	argv = split_line(line);
	if (!argv[0])
	{
		free_argv(argv);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (ft_strchr(argv[0], '/'))
			path = argv[0];
		else
			path = find_executable(argv[0]);
		if (path)
			execve(path, argv, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("fork");
	if (path && path != argv[0])
		free(path);
	free_argv(argv);
}

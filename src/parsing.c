/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 03:51:04 by emetel            #+#    #+#             */
/*   Updated: 2025/05/20 01:12:26 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	handle_line(char *line, char **av, char **env)
{
	pid_t	pid;
	char	*path;

	path = NULL;
	(void)line;
	if (!av[0])
	{
		free_argv(av);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (ft_strchr(av[0], '/'))
			path = av[0];
		else
			path = find_executable(av[0]);
		if (path)
			execve(path, av, env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("fork");
	if (path && path != av[0])
		free(path);
	free_argv(av);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:01:33 by mkettab           #+#    #+#             */
/*   Updated: 2025/05/20 23:46:10 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_type	*handle_line(char *line, char **env)
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
	printf("LIGNE=%s\n", line);
	if (!av[0])
	{
		free_argv(av);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (line[1] == '<')
			command->token = HEREDOC;
		if (line[1] == ' ')
			command->token = IN;
		else
			command->token = ERROR;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 01:33:31 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/14 03:27:53 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char*	expand_heredoc(char* line, t_sys* sys)
{
	int	i;
	int start;
	char	*line_extended;

	i = 0;
	start = 0;
	line_extended = gc_strdup("", &(sys->garbage));
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (i > start)
				line_extended = gc_strjoin(line_extended, gc_substr(line, start, i, &(sys->garbage)), $(sys->garbage));

		}
	}
}

int	handle_heredoc(char* delimiter, t_sys* sys)
{
	int		pipe_fd[2];
	char	*line;
	char	*line_expanded;
	
	(void)sys;
	if (pipe(pipe_fd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (!ft_strcmp(line, delimiter)
				&& ft_strlen(line) == ft_strlen(delimiter))
		{
			free(line);
			break;
		}
		line_expanded = line;
		ft_putstr_fd(line_expanded, pipe_fd[1]);
		ft_putstr_fd("\n", pipe_fd[1]);
		free(line);
	}
	close(pipe_fd[1]);
	return pipe_fd[0];
}
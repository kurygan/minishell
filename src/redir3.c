/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:05:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 14:58:25 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	process_heredoc_line(char *line, char *delimiter, \
	int pipe_fd, t_sys *sys)
{
	char	*line_expanded;

	if (!(delimiter[0] == '\'' || delimiter[0] == '\"'))
		line_expanded = expand_heredoc(line, sys);
	else
		line_expanded = line;
	ft_putstr_fd(line_expanded, pipe_fd);
	ft_putstr_fd("\n", pipe_fd);
}

static char	*get_unquoted_delimiter(char *delimiter, t_sys *sys)
{
	int	i;

	i = 0;
	if (delimiter[0] == '\'' || delimiter[0] == '\"')
		return (extract_quoted_target(delimiter, &i, delimiter[0], sys));
	else
		return (delimiter);
}

static int	read_heredoc_lines(int pipe_fd, char *delimiter, \
	char *unquoted_del, t_sys *sys)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || (!ft_strcmp(line, unquoted_del) && \
			ft_strlen(line) == ft_strlen(unquoted_del)))
		{
			if (line)
				free(line);
			return (1);
		}
		process_heredoc_line(line, delimiter, pipe_fd, sys);
		free(line);
	}
}

int	handle_heredoc(char *delimiter, t_sys *sys)
{
	int		pipe_fd[2];
	char	*unquoted_del;

	if (pipe(pipe_fd) == -1)
		return (-1);
	unquoted_del = get_unquoted_delimiter(delimiter, sys);
	read_heredoc_lines(pipe_fd[1], delimiter, unquoted_del, sys);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

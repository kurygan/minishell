/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 01:33:31 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/15 20:46:52 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char*	expand_heredoc(char* line, t_sys* sys)
{
	int	i;
	int start;
	char	*line_extended;
	char	*var_expanded;

	i = 0;
	start = 0;
	line_extended = gc_strdup("", &(sys->garbage));
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (i > start)
			{
				line_extended = gc_strjoin(line_extended, gc_substr(line, start, i, &(sys->garbage)), &(sys->garbage));
				start = i;
			}
			i++;
			while (ft_isalnum(line[i]) || line[i] == '_')
				i++;
			var_expanded = expand_var(gc_substr(line, start, i, &(sys->garbage)), sys, sys->exit_status);
			line_extended = gc_strjoin(line_extended, var_expanded, &(sys->garbage));
		}
		else
			i++;
	}
	return line_extended;
}

int	handle_heredoc(char* delimiter, t_sys* sys)
{
	int		pipe_fd[2];
	char	*line;
	char	*line_expanded;
	char	*unquoted_del;
	int		i;
	
	(void)sys;
	if (pipe(pipe_fd) == -1)
		return (-1);
	i = 0;
	if (delimiter[0] == '\'' || delimiter[0] == '\"')
		unquoted_del = extract_quoted_target(delimiter, &i, delimiter[0], sys);
	else
		unquoted_del = delimiter;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (!ft_strcmp(line, unquoted_del)
				&& ft_strlen(line) == ft_strlen(unquoted_del))
		{
			free(line);
			break;
		}
		if (!(delimiter[0] == '\'' || delimiter[0] == '\"'))
			line_expanded = expand_heredoc(line, sys);
		else
			line_expanded = line;
		ft_putstr_fd(line_expanded, pipe_fd[1]);
		ft_putstr_fd("\n", pipe_fd[1]);
		free(line);
	}
	close(pipe_fd[1]);
	return pipe_fd[0];
}

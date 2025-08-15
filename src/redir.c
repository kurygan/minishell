/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 01:33:31 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/16 00:01:04by mkettab          ###   ########.fr       */
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

int handle_redir_in(t_cmd_segment* cmd, t_sys* sys)
{
	int pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	close(pipe_fd[1]);
	if (!cmd->infile || !cmd->heredoc)
		return (close(pipe_fd[0]), -1);
	if (cmd->infile)
	{
		pipe_fd[0] = open(cmd->infile, O_RDONLY, 0777);
		if (pipe_fd[0] < 0)
		{
			if (access(cmd->infile, F_OK) == 0)
				printf("Permission Denied\n");
			else
				printf("Error: No such file\n");
		}
	}
	else if (cmd->heredoc)
		pipe_fd[0] = handle_heredoc(cmd->heredoc, sys);
	return (pipe_fd[0]);
}

int	handle_redir_out(t_cmd_segment *cmd)
{
	int pipe_fd[2];
	
	if (pipe(pipe_fd) == -1)
		return -1;
	close(pipe_fd[0]);
	if (!cmd->outfile)
		return (close(pipe_fd[1]), -1);
	if (cmd->append_mode)
		pipe_fd[1] = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		pipe_fd[1] = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipe_fd[1] == -1)
		printf("Error: Permission denied");
	return pipe_fd[1];
}

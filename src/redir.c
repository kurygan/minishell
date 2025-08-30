/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 01:33:31 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/30 13:52:10 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*process_dollar_var(char *line, int *i, int *start, t_sys *sys)
{
	char	*result;

	*start = *i;
	(*i)++;
	while (ft_isalnum(line[*i]) || line[*i] == '_')
		(*i)++;
	result = expand_var(gc_substr(line, *start, *i, &(sys->garbage)), \
			sys, sys->exit_status);
	*start = *i;
	return (result);
}

char	*expand_heredoc(char *line, t_sys *sys)
{
	int		i;
	int		start;
	char	*result;

	(void)0, i = 0, start = 0;
	result = gc_strdup("", &(sys->garbage));
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (i > start)
				result = gc_strjoin(result, gc_substr(line, start, i, \
						&(sys->garbage)), &(sys->garbage));
			result = gc_strjoin(result, process_dollar_var(line, &i, \
					&start, sys), &(sys->garbage));
		}
		else
			i++;
	}
	if (i > start)
		result = gc_strjoin(result, gc_substr(line, start, i, \
				&(sys->garbage)), &(sys->garbage));
	if (!result[0])
		result = gc_strdup(line, &(sys->garbage));
	return (result);
}

int	handle_heredoc(char *delimiter, t_sys *sys)
{
	int		pipe_fd[2];
	char	*line;
	char	*line_expanded;
	char	*unquoted_del;
	int		i;

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
			break ;
		if (!ft_strcmp(line, unquoted_del)
			&& ft_strlen(line) == ft_strlen(unquoted_del))
		{
			free(line);
			break ;
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
	return (pipe_fd[0]);
}

int	handle_redir_in(t_cmd_segment *cmd, t_sys *sys)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	close(pipe_fd[1]);
	if (!cmd->infile && !cmd->heredoc)
		return (close(pipe_fd[0]), -1);
	if (cmd->infile)
	{
		pipe_fd[0] = open(cmd->infile, O_RDONLY, 0777);
		if (pipe_fd[0] < 0)
		{
			if (access(cmd->infile, F_OK) == 0)
				ft_printf("%s: Permission denied\n", cmd->infile);
			else
				ft_printf("%s: No such file or directory\n", cmd->infile);
		}
	}
	else if (cmd->heredoc)
		pipe_fd[0] = handle_heredoc(cmd->heredoc, sys);
	return (pipe_fd[0]);
}

int	handle_redir_out(t_cmd_segment *cmd)
{
	int			pipe_fd[2];
	t_type		*outfiles;
	struct stat	statbuf;

	if (pipe(pipe_fd) == -1)
		return (-1);
	close(pipe_fd[0]);
	if (!cmd->outfiles)
		return (close(pipe_fd[1]), -1);
	outfiles = cmd->outfiles;
	while (outfiles)
	{
		if (outfiles && outfiles->token == REDIR_APPEND)
			pipe_fd[1] = open(outfiles->str, O_WRONLY | O_CREAT | O_APPEND, \
							0644);
		else if (outfiles && outfiles->token == REDIR_OUT)
			pipe_fd[1] = open(outfiles->str, O_WRONLY | O_CREAT | O_TRUNC, \
							0644);
		if (pipe_fd[1] == -1)
		{
			if (stat(outfiles->str, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
				ft_printf("%s: Is a directory\n", outfiles->str);
			else
				ft_printf("%s: Permission denied\n", outfiles->str);
			break ;
		}
		outfiles = outfiles->next;
	}
	return (pipe_fd[1]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:00:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 14:58:25 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	open_input_file(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY, 0777);
	if (fd < 0)
	{
		if (access(infile, F_OK) == 0)
			ft_printf("%s: Permission denied\n", infile);
		else
			ft_printf("%s: No such file or directory\n", infile);
	}
	return (fd);
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
		pipe_fd[0] = open_input_file(cmd->infile);
	else if (cmd->heredoc)
		pipe_fd[0] = handle_heredoc(cmd->heredoc, sys);
	return (pipe_fd[0]);
}

static int	open_output_file(t_type *outfile)
{
	int			fd;
	struct stat	statbuf;

	if (outfile->token == REDIR_APPEND)
		fd = open(outfile->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (outfile->token == REDIR_OUT)
		fd = open(outfile->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = -1;
	if (fd == -1)
	{
		if (stat(outfile->str, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
			ft_printf("%s: Is a directory\n", outfile->str);
		else
			ft_printf("%s: Permission denied\n", outfile->str);
	}
	return (fd);
}

int	handle_redir_out(t_cmd_segment *cmd)
{
	int		pipe_fd[2];
	t_type	*outfiles;

	if (pipe(pipe_fd) == -1)
		return (-1);
	close(pipe_fd[0]);
	if (!cmd->outfiles)
		return (close(pipe_fd[1]), -1);
	outfiles = cmd->outfiles;
	while (outfiles)
	{
		pipe_fd[1] = open_output_file(outfiles);
		if (pipe_fd[1] == -1)
			break ;
		outfiles = outfiles->next;
	}
	return (pipe_fd[1]);
}

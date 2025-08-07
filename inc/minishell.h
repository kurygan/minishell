/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:52:13 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/08 00:31:53 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "../lib/libft.h"
# include "garbage.h"

# ifndef ECHOCTL
#  define ECHOCTL 0000001000
# endif

typedef enum e_token
{
	CMD,
	ARGS,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_TARGET,
	OPTIONS,
	ERROR
}	t_token;

typedef struct s_cmd_segment
{
	char					*cmd;
	char					**args;
	char					**options;
	char					*infile;
	char					*heredoc;
	char					*outfile;
	int						append_mode;
	struct s_sys *sys;
	struct s_cmd_segment	*next;
	struct s_cmd_segment	*prev;
}	t_cmd_segment;

typedef struct s_type
{
	char					*str;
	t_token					token;
	struct s_sys			*sys;
	struct s_type			*next;
	struct s_type			*prev;
}	t_type;

typedef struct s_sys
{
	char			**env;
	t_cmd_segment	*command;
	t_type			*tokens;
	struct _gc				*garbage;
}	t_sys;

/* expander */

void			expand_variables(t_cmd_segment *segments, t_sys *sys,
					int exit_status);

/* handle_redirection */

void			handle_redirection(char *line, int *i, t_type **lst, t_sys *sys);

/* parsing */

t_cmd_segment	*handle_line(t_sys *sys, int exit_status);

/* segment */

void			handle_command_token(t_type *token, t_cmd_segment **current,
					t_cmd_segment **head, t_sys *sys);
void			handle_redirection_token(t_type *token,
					t_cmd_segment **current, t_cmd_segment **head, t_sys *sys);
void			handle_option_token(t_type *token, t_cmd_segment **current,
					t_cmd_segment **head, t_sys *sys);
t_cmd_segment	*convert_tokens(t_sys *sys);

/* signal */

void			sigint_handler(int sig);
void			setup_signals(struct termios *orig_termios);
void			reset_signals(struct termios *orig_termios);

/* token */

t_type			*tokenize(char *line, t_sys *sys);
t_type			*add_token(t_type *list, char *str, t_token token, t_sys *sys);
void			handle_pipe(char *line, int *i, t_type **lst, t_sys *sys);
void			handle_quote(char *line, int *i, t_type **lst, t_sys *sys);
void			handle_word(char *line, int *i, t_type **lst, t_sys *sys);

/* debug */

void			debug_print_segments(t_cmd_segment *seg);
void			debug_print_tokens(t_type *tokens);
void			free_segments(t_cmd_segment *segments);
void			free_token_list(t_type *lst);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:52:13 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/03 18:00:50 by emetel           ###   ########.fr       */
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
# include "../lib/libft.h"

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
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
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
	struct s_cmd_segment	*next;
}	t_cmd_segment;

typedef struct s_type
{
	char					*str;
	t_token					token;
	struct s_type			*next;
	struct s_type			*prev;
}	t_type;

/* expander */

void			expand_variables(t_cmd_segment *segments, char **env,
					int exit_status);

/* expand_quote */

char			*expand_quote(char *arg, char **env, int exit_status,
					int is_single_quote);

/* quote_utils */

char			*get_env_value(char *var_name, char **env);
char			*remove_quotes(char *str);
char			*process_regular_char(char *content, char *result, int *i);
char			*process_valid_variable(char *content, char *result, char **env,
					int *i);
char			*process_invalid_variable(char *content, char *result, int *i);

/* expand_utils */

void			expand_quoted_str(char **str, char **env, int exit_status,
					int is_single);
void			expand_variable_str(char **str, char **env, int exit_status);
char			*extract_var_content(char *content, int *i, int start);

/* handle_redirection */

void			handle_redirection(char *line, int *i, t_type **lst);

/* parsing */

t_cmd_segment	*handle_line(char *line, char **env, int exit_status);

/* segment */

void			handle_command_token(t_type *token, t_cmd_segment **current,
					t_cmd_segment **head);
void			handle_redirection_token(t_type *token, t_type **next,
					t_cmd_segment **current, t_cmd_segment **head);
void			handle_option_token(t_type *token, t_cmd_segment **current,
					t_cmd_segment **head);
t_cmd_segment	*init_segment(void);
t_cmd_segment	*convert_tokens(t_type *tokens);

/* signal */

void			sigint_handler(int sig);
void			setup_signals(struct termios *orig_termios);
void			reset_signals(struct termios *orig_termios);

/* token */

t_type			*tokenize(char *line);
t_type			*add_token(t_type *list, char *str, t_token token);
void			handle_pipe(char *line, int *i, t_type **lst);
void			handle_quote(char *line, int *i, t_type **lst, char quote);
void			handle_word(char *line, int *i, t_type **lst);

/* debug */

void			debug_print_segments(t_cmd_segment *seg);
void			debug_print_tokens(t_type *tokens);
void			free_segments(t_cmd_segment *segments);
void			free_token_list(t_type *lst);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:52:13 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/30 15:07:53 by emetel           ###   ########.fr       */
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

typedef enum e_token			t_token;
typedef struct s_cmd_segment	t_cmd_segment;
typedef struct s_type			t_type;
typedef struct s_sys			t_sys;
typedef struct s_env_var		t_env_var;
typedef struct s_gc				t_gc;

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
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	ERROR
}	t_token;

typedef struct s_cmd_segment
{
	char			*cmd;
	char			**args;
	char			*infile;
	char			*heredoc;
	t_type			*outfiles;
	t_sys			*sys;
	t_cmd_segment	*next;
	t_cmd_segment	*prev;
}	t_cmd_segment;

typedef struct s_type
{
	char					*str;
	t_token					token;
	struct s_sys			*sys;
	struct s_type			*next;
	struct s_type			*prev;
}	t_type;

typedef struct s_env_var
{
	char				*key;
	char				*value;
	bool				exported;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_sys
{
	char			**env;
	t_env_var		*env_list;
	t_gc			*env_gc;
	t_cmd_segment	*command;
	t_type			*tokens;
	int				exit_status;
	t_gc			*garbage;
	bool			env_was_empty;
}	t_sys;

// Global variable for signal handling
extern int			g_signal_received;

/* expander */

void			expand_variables(t_cmd_segment *segments, t_sys *sys,
					int exit_status);
int				count_exported_vars(t_env_var *env_list);
void			sort_env_array(t_env_var **array, int size);
void			print_sorted_export_list(t_env_var **array, int count);

/* expand_quote */

char			*expand_quote(char *arg, t_sys *sys, int exit_status,
					int is_single_quote);

/* quote_utils */

char			*remove_quotes(char *str, t_sys *sys);
char			*process_regular_char(char *content, char *result, int *i, \
					struct s_gc **garbage);
char			*process_valid_variable(char *content, char *result, t_sys *sys,
					int *i);
char			*process_invalid_variable(char *content, char *result, int *i, \
					struct s_gc **garbage);
char			*extract_quoted_target(char *line, int *i, char quote, \
					t_sys *sys);

/* expand_utils */

char			*expand_var(char *arg, t_sys *sys, int exit_status);
char			*expand_tilde(char *arg, t_sys *sys);
char			*process_quoted_arg(char *arg, t_sys *sys, int exit_status);
char			*expand_variables_in_dquotes(char *content, t_sys *sys,
					int exit_status);
void			expand_quoted_str(char **str, t_sys *sys, int exit_status,
					int is_single);
void			expand_variable_str(char **str, t_sys *sys, int exit_status);

/* expand_utils2 */

int				has_mixed_quotes(char *original);
int				check_mixed_quotes_in_quoted(char *original, int *i);
int				check_mixed_quotes_in_unquoted(char *original, int *i);
int				process_quoted_part(char *str, int *i, char **result, \
					t_sys *sys);
int				process_unquoted_part(char *str, int *i, char **result, \
					t_sys *sys);
char			*extract_var_content(char *content, int *i, int start, \
					struct s_gc **garbage);

/* handle_redirection */

void			handle_redirection(char *line, int *i, t_type **lst, \
					t_sys *sys);
int				handle_redir_in(t_cmd_segment *cmd, t_sys *sys);
int				handle_redir_out(t_cmd_segment *cmd);

/* parsing */

t_cmd_segment	*handle_line(t_sys *sys);

/* segment */

void			handle_command_token(t_type *token, t_cmd_segment **current,
					t_cmd_segment **head, t_sys *sys);
void			handle_redirection_token(t_type *token,
					t_cmd_segment **current, t_cmd_segment **head, t_sys *sys);
t_cmd_segment	*convert_tokens(t_sys *sys);

/* signal */

void			sigint_handler(int sig);
void			setup_signals(struct termios *orig_termios);
void			reset_signals(struct termios *orig_termios);
void			setup_exec_signals(void);
void			setup_interactive_signals(void);

/* token */

bool			check_unclosed_quotes(char *line);
t_type			*tokenize(char *line, t_sys *sys);
t_type			*add_token(t_type *list, char *str, t_token token, t_sys *sys);
void			handle_pipe(int *i, t_type **lst, t_sys *sys);
void			handle_quote(char *line, int *i, t_type **lst, t_sys *sys);
char			*extract_quoted_arg(char *line, int *i, char quote, t_sys *sys);
char			*extract_complete_word(char *line, int *i, t_sys *sys);
void			handle_word(char *line, int *i, t_type **lst, t_sys *sys);
bool			is_redirection_token(t_token token);
bool			should_become_args(t_type *tmp);

/* exec */

void			exec(t_sys *sys);
bool			is_builtin(char	*cmd);
void			exec_builtin(t_cmd_segment *cmd);
void			exec_cd(t_cmd_segment *cmd);
void			exec_echo(t_cmd_segment *cmd);
void			exec_env(t_cmd_segment *cmd);
void			exec_pwd(t_cmd_segment *cmd);

/* cd_utils */

void			update_pwd_variables(t_cmd_segment *cmd, char *old_pwd);
int				change_directory(char *path, t_cmd_segment *cmd);

/* exec_utils */

char			*get_path(char *cmd, t_sys *sys);
void			fd_redir(t_cmd_segment *cmd, int cmd_index, int total_cmds, \
					int **pipes);
char			**get_args(t_cmd_segment *command);
int				**create_pipes(int pipe_count, t_sys *sys);
void			close_all_pipes(int **pipes, int pipe_count);
int				count_args(char **args);
char			**build_args_array(t_cmd_segment *command, int arg_count);
void			exec_pipeline(t_cmd_segment *segments, t_sys *sys);
void			exec_single_builtin(t_cmd_segment *command);
int				count_commands(t_cmd_segment *segments);
void			wait_pid(pid_t pid, t_sys *sys, int i, int total);
void			exec_child_process(t_cmd_segment *cmd, int **pipes, \
					int cmd_index, int total_cmds);

/* env management */
t_env_var		*create_env_var(char *key, char *value, t_sys *sys);
t_env_var		*parse_env_string(char *env_str, t_sys *sys);
t_env_var		*init_env_list(char **env, t_sys *sys);
char			**env_list_to_array(t_env_var *env_list, t_sys *sys);
t_env_var		*find_env_var(t_env_var *env_list, char *key);
void			add_env_var(t_env_var **env_list, char *key, char *value, \
					t_sys *sys);
void			add_env_var_exported(t_env_var **env_list, char *key, \
					char *value, t_sys *sys);
void			update_env_var(t_env_var *env_var, char *value, t_sys *sys);
void			remove_env_var(t_env_var **env_list, char *key, t_sys *sys);
void			free_env_list(t_env_var *env_list, t_sys *sys);
void			free_env_list_safe(t_env_var *env_list);
char			*get_env_value_from_list(char *var_name, t_env_var *env_list);
void			increment_shlvl(t_env_var *env_list, t_sys *sys);
void			print_shlvl_warning(int level);

/* export management */
void			exec_export(t_cmd_segment *cmd);
bool			is_valid_identifier(char *str);
char			*extract_key_value(char *arg, char **value, t_sys *sys);
char			*handle_plus_equal(char *arg, char **value, t_sys *sys);
void			insert_env_var_sorted(t_env_var **env_list, char *key, \
					char *value, t_sys *sys);
void			print_export_list(t_env_var *env_list, t_sys *sys);
void			add_or_update_var(t_env_var **env_list, char *key, \
					char *value, t_sys *sys);
void			add_or_append_var(t_env_var **env_list, char *key, \
					char *value, t_sys *sys);
void			process_export_arg(char *arg, t_env_var **env_list, t_sys *sys, \
					bool *error_occurred);

/* unset management*/

void			exec_unset(t_cmd_segment *cmd);

/* exit management*/

void			exec_exit(t_cmd_segment *cmd);

/* redir */

int				handle_heredoc(char *delimiter, t_sys *sys);

/* redir */

int				handle_redir_out(t_cmd_segment *cmd);
int				handle_redir_in(t_cmd_segment *cmd, t_sys *sys);
int				handle_heredoc(char *delimiter, t_sys *sys);
void			process_heredoc_line(char *line, char *delimiter, \
					int pipe_fd, t_sys *sys);
char			*expand_heredoc(char *line, t_sys *sys);

/*error management*/
bool			check_synthax_error(t_sys *sys, char *line);
int				check_initial_pipe(t_sys *sys);
int				check_token_syntax(t_type *current);
void			handle_syntax_error(t_sys *sys, char *line);
bool			double_pipe_check(t_type *token);
bool			pipe_and_redir_check(t_type *token);
t_sys			*init_system(char **env);
int				cleanup_and_exit(t_sys *sys, struct termios *orig_termios);

#endif
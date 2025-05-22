/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:52:13 by mkettab           #+#    #+#             */
/*   Updated: 2025/05/22 02:26:09 by emetel           ###   ########.fr       */
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

typedef enum e_token
{
	CMD,
	ARGS,
	PIPE,
	IN,
	TRUNCATE,
	APPEND,
	HEREDOC,
	ERROR
}	t_token;

typedef struct s_cmd_segment
{
	char					*cmd;
	char					**args;
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

/* parsing */

t_cmd_segment	*handle_line(char *line, char **env, int exit_status);

/* token */

t_type			*tokenize(char *line);
t_type			*add_token(t_type *list, char *str, t_token token);
void			handle_pipe(char *line, int *i, t_type **lst);
void			handle_redirection(char *line, int *i, t_type **lst);
void			handle_quote(char *line, int *i, t_type **lst, char quote);
void			handle_word(char *line, int *i, t_type **lst);
t_cmd_segment	*convert_tokens(t_type *tokens);

/* expander */

void			expand_variables(t_cmd_segment *segments, char **env,
					int exit_status);

/* debug */
					
void			debug_print_segments(t_cmd_segment *seg);
void			free_segments(t_cmd_segment *segments);
void			free_token_list(t_type *lst);
					
#endif
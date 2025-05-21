/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:52:13 by mkettab           #+#    #+#             */
/*   Updated: 2025/05/21 23:41:07 by mkettab          ###   ########.fr       */
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
# include "garbage.h"

typedef enum
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

typedef struct s_type
{
	char	*str;
	t_token	token;
	struct s_type	*next;
	struct s_type	*prev;
}	t_type;

typedef struct s_sys
{
	t_gc	*gc;
	t_type	*type;
}	t_sys;

/* parsing */

t_type	*handle_line(char *line, char **env);

/* minishell */

void	read_input_loop(char **av, char **env);

#endif
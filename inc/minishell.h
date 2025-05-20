/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:52:13 by mkettab           #+#    #+#             */
/*   Updated: 2025/05/20 16:09:22 by mkettab          ###   ########.fr       */
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

typedef enum
{
	CMD,
	ARGS,
	PIPE,
	IN,
	TRUNCATE,
	APPEND,
	HEREDOC
}	t_token;

typedef struct s_type
{
	char	*str;
	t_token	token;
	t_type	*next;
	t_type	*prev;
}	t_type;

/* parsing */

t_type	*handle_line(char *line, int ac, char **av, char **env);

/* minishell */

void	read_input_loop(char **av, char **env);

#endif
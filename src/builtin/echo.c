/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:10:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/28 20:28:00 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	is_n_option(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (false);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (i > 1);
}

static void	process_echo_arg(char *arg, bool *print, bool *options_ended, \
		bool *no_newline)
{
	if (!*options_ended && is_n_option(arg))
		*no_newline = true;
	else
	{
		*options_ended = true;
		if (*print && arg && arg[0] != '\0')
			ft_putchar_fd(' ', 1);
		if (arg && arg[0] != '\0')
		{
			*print = true;
			ft_putstr_fd(arg, 1);
		}
	}
}

static void	print_echo_args(char **args, bool *no_newline)
{
	bool	print;
	bool	options_ended;
	int		i;

	print = false;
	options_ended = false;
	i = 0;
	while (args && args[i])
	{
		process_echo_arg(args[i], &print, &options_ended, no_newline);
		i++;
	}
}

void	exec_echo(t_cmd_segment *cmd)
{
	char	**args;
	bool	no_newline;

	args = cmd->args;
	no_newline = false;
	print_echo_args(args, &no_newline);
	if (!no_newline)
		ft_putchar_fd('\n', 1);
}

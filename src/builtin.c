/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 01:46:05 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/20 11:24:03 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_builtin(char	*cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") \
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") \
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") \
		|| !ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}

static bool	check_n_option(char **options)
{
	int	i;

	if (!options)
		return (false);
	i = 0;
	while (options[i])
	{
		if (is_option(options[i]))
			return (true);
		i++;
	}
	return (false);
}

void	exec_echo(t_cmd_segment *cmd)
{
	char	**args;
	bool	print;
	bool	no_newline;

	no_newline = check_n_option(cmd->options);
	args = cmd->args;
	print = false;
	if (args)
	{
		while (*args)
		{
			if (print)
				printf(" ");
			print = true;
			printf("%s", *args);
			args++;
		}
	}
	if (!no_newline)
		printf("\n");
}

void	exec_pwd(t_cmd_segment *cmd)
{
	char	*cwd;

	(void)cmd;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("pwd");
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
}

void	exec_builtin(t_cmd_segment *cmd)
{
	if (!(ft_strcmp(cmd->cmd, "echo")))
		exec_echo(cmd);
	else if (!(ft_strcmp(cmd->cmd, "pwd")))
		exec_pwd(cmd);
}

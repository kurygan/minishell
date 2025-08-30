/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:55:06 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 16:04:38 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_plus_equal_error(char *arg, bool *error_occurred)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	*error_occurred = true;
}

static char	*process_plus_equal_value(char *value, t_sys *sys)
{
	if (value && (*value == ' ' || *value == '\t'))
	{
		while (*value == ' ' || *value == '\t')
			value++;
		if (!*value)
			return (NULL);
		else
			return (remove_quotes(value, sys));
	}
	else if (value)
		return (remove_quotes(value, sys));
	return (value);
}

void	process_plus_equal(char *arg, t_env_var **env_list, t_sys *sys, \
			bool *error_occurred)
{
	char		*key;
	char		*value;
	char		*plus_pos;
	char		*identifier;

	plus_pos = ft_strnstr(arg, "+=", ft_strlen(arg));
	identifier = gc_substr(arg, 0, plus_pos - arg, &(sys->garbage));
	if (!is_valid_identifier(identifier))
	{
		handle_plus_equal_error(arg, error_occurred);
		return ;
	}
	key = gc_strdup(identifier, &(sys->garbage));
	value = gc_strdup(plus_pos + 2, &(sys->garbage));
	value = process_plus_equal_value(value, sys);
	add_or_append_var(env_list, key, value, sys);
}

void	exec_export(t_cmd_segment *cmd)
{
	int		i;
	bool	error_occurred;

	if (!cmd->args || !cmd->args[0])
	{
		print_export_list(cmd->sys->env_list, cmd->sys);
		return ;
	}
	error_occurred = false;
	i = 0;
	while (cmd->args[i])
	{
		process_export_arg(cmd->args[i], &cmd->sys->env_list, cmd->sys, \
			&error_occurred);
		i++;
	}
	if (error_occurred)
		cmd->sys->exit_status = 1;
	else
		cmd->sys->exit_status = 0;
}

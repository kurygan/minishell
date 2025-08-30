/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:55:06 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 14:39:40 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	if (!ft_isalpha(*str) && *str != '_')
		return (false);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

char	*extract_key_value(char *arg, char **value, t_sys *sys)
{
	char		*equal_pos;
	char		*plus_equal_pos;
	char		*key;
	char		*raw_value;

	plus_equal_pos = ft_strnstr(arg, "+=", ft_strlen(arg));
	equal_pos = ft_strchr(arg, '=');
	if (!equal_pos)
	{
		*value = NULL;
		return (gc_strdup(arg, &(sys->garbage)));
	}
	if (plus_equal_pos && plus_equal_pos == equal_pos)
		return (handle_plus_equal(arg, value, sys));
	key = gc_substr(arg, 0, equal_pos - arg, &(sys->garbage));
	raw_value = gc_strdup(equal_pos + 1, &(sys->garbage));
	if (raw_value && (*raw_value == ' ' || *raw_value == '\t'))
	{
		while (*raw_value == ' ' || *raw_value == '\t')
			raw_value++;
		if (!*raw_value)
		{
			*value = NULL;
			return (key);
		}
	}
	*value = remove_quotes(raw_value, sys);
	return (key);
}

void	add_or_update_var(t_env_var **env_list, char *key, char *value, \
			t_sys *sys)
{
	t_env_var	*existing_var;

	existing_var = find_env_var(*env_list, key);
	if (existing_var)
	{
		update_env_var(existing_var, value, sys);
		existing_var->exported = true;
	}
	else
	{
		add_env_var_exported(env_list, key, value, sys);
	}
}

void	add_or_append_var(t_env_var **env_list, char *key, char *value, \
			t_sys *sys)
{
	t_env_var	*existing_var;
	char		*new_value;

	existing_var = find_env_var(*env_list, key);
	if (existing_var && existing_var->value && value)
	{
		new_value = gc_strjoin(existing_var->value, value, &(sys->env_gc));
		update_env_var(existing_var, new_value, sys);
	}
	else if (existing_var)
	{
		update_env_var(existing_var, value, sys);
	}
	else
	{
		add_env_var_exported(env_list, key, value, sys);
	}
}

void	insert_env_var_sorted(t_env_var **env_list, char *key, char *value, \
			t_sys *sys)
{
	t_env_var	*new_var;
	t_env_var	*current;
	t_env_var	*prev;

	new_var = create_env_var(key, value, sys);
	new_var->exported = true;
	if (!new_var)
		return ;
	if (!*env_list || ft_strcmp(new_var->key, (*env_list)->key) < 0)
	{
		new_var->next = *env_list;
		*env_list = new_var;
		return ;
	}
	current = *env_list;
	prev = NULL;
	while (current && ft_strcmp(new_var->key, current->key) > 0)
	{
		prev = current;
		current = current->next;
	}
	prev->next = new_var;
	new_var->next = current;
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
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		*error_occurred = true;
		return ;
	}
	key = gc_strdup(identifier, &(sys->garbage));
	value = gc_strdup(plus_pos + 2, &(sys->garbage));
	if (value && (*value == ' ' || *value == '\t'))
	{
		while (*value == ' ' || *value == '\t')
			value++;
		if (!*value)
		{
			value = NULL;
		}
		else
		{
			value = remove_quotes(value, sys);
		}
	}
	else if (value)
	{
		value = remove_quotes(value, sys);
	}
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

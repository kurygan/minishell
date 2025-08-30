/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:37:06 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/30 15:01:41 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_export_error(char *arg, bool *error_occurred)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	*error_occurred = true;
}

static void	process_with_equal(char *arg, t_env_var **env_list, t_sys *sys,
	bool *error_occurred)
{
	char	*key;
	char	*value;
	char	*equal_pos;
	char	*identifier;

	equal_pos = ft_strchr(arg, '=');
	identifier = gc_substr(arg, 0, equal_pos - arg, &(sys->garbage));
	if (!is_valid_identifier(identifier))
	{
		print_export_error(arg, error_occurred);
		return ;
	}
	key = extract_key_value(arg, &value, sys);
	add_or_update_var(env_list, key, value, sys);
}

static void	process_without_equal(char *arg, t_env_var **env_list, t_sys *sys,
	bool *error_occurred)
{
	char	*key;
	char	*value;

	if (!is_valid_identifier(arg))
	{
		print_export_error(arg, error_occurred);
		return ;
	}
	key = gc_strdup(arg, &(sys->garbage));
	value = NULL;
	add_or_update_var(env_list, key, value, sys);
}

static void	handle_plus_equal_local(char *arg, t_env_var **env_list, t_sys *sys,
	bool *error_occurred)
{
	char	*equal_pos;
	char	*identifier;
	char	*key;
	char	*value;

	equal_pos = ft_strnstr(arg, "+=", ft_strlen(arg));
	identifier = gc_substr(arg, 0, equal_pos - arg, &(sys->garbage));
	if (!is_valid_identifier(identifier))
	{
		print_export_error(arg, error_occurred);
		return ;
	}
	key = handle_plus_equal(arg, &value, sys);
	if (key)
		add_or_update_var(env_list, key, value, sys);
	else
		*error_occurred = true;
}

void	process_export_arg(char *arg, t_env_var **env_list, t_sys *sys,
	bool *error_occurred)
{
	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
	{
		handle_plus_equal_local(arg, env_list, sys, error_occurred);
		return ;
	}
	if (ft_strchr(arg, '='))
		process_with_equal(arg, env_list, sys, error_occurred);
	else
		process_without_equal(arg, env_list, sys, error_occurred);
}

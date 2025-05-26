/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:50:01 by emetel            #+#    #+#             */
/*   Updated: 2025/05/22 02:18:36 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*expand_var(char *arg, char **env, int exit_status)
{
	int		i;
	char	*var_name;
	char	*value;
	size_t	len;

	if (!arg || arg[0] != '$')
		return (ft_strdup(arg));
	if (arg[1] == '?')
		return (ft_itoa(exit_status));
	var_name = arg + 1;
	len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, len) && env[i][len] == '=')
		{
			value = env[i] + len + 1;
			return (ft_strdup(value));
		}
		i++;
	}
	return (ft_strdup(""));
}

void	expand_variables(t_cmd_segment *segments, char **env, int exit_status)
{
	int				i;
	char			*expanded;
	t_cmd_segment	*current;

	current = segments;
	while (current)
	{
		i = 0;
		while (current->args && current->args[i])
		{
			if (current->args[i][0] == '$')
			{
				expanded = expand_var(current->args[i], env, exit_status);
				free(current->args[i]);
				current->args[i] = expanded;
			}
			i++;
		}
		current = current->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:00:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/29 20:43:05 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*expand_tilde(char *arg, t_sys *sys)
{
	char	*home;
	char	*result;

	if (!arg || arg[0] != '~')
		return (gc_strdup(arg, &(sys->garbage)));
	home = get_env_value_from_list("HOME", sys->env_list);
	if (!home)
		return (gc_strdup(arg, &(sys->garbage)));
	if (arg[1] == '\0' || arg[1] == '/')
	{
		if (arg[1] == '\0')
			result = gc_strdup(home, &(sys->garbage));
		else
			result = gc_strjoin(home, arg + 1, &(sys->garbage));
	}
	else
		return (gc_strdup(arg, &(sys->garbage)));
	return (result);
}

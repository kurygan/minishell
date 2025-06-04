/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:58:20 by emetel            #+#    #+#             */
/*   Updated: 2025/06/04 04:41:14 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	count_options(char **options)
{
	int	i;

	i = 0;
	if (options)
	{
		while (options[i])
			i++;
	}
	return (i);
}

static int	fill_options_array(char **new_options, char **old_options,
		t_sys *sys)
{
	int	i;
	char	*new_options;

	i = 0;
	new_options = sys->type->str;
	if (old_options)
	{
		while (old_options[i])
		{
			new_options[i] = old_options[i];
			i++;
		}
	}
	new_options[i] = gc_strdup(new_options, &sys->gc, type);
	if (!new_options[i])
		return (0);
	new_options[i + 1] = 0;
	return (1);
}

void	handle_option_token(t_sys *sys, t_cmd_segment **current)
{
	int		count;
	char	**new_options;

	if (!*current)
	{
		*current = init_segment(sys);
		if (!sys->cmd)
			sys->cmd = *current;
	}
	if (!*current || !sys->type)
		return ;
	count = count_options((*current)->options);
	new_options = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_options)
		return ;
	if (!fill_options_array(new_options, (*current)->options, sys))
	{
		free(new_options);
		return ;
	}
	if ((*current)->options)
		free((*current)->options);
	(*current)->options = new_options;
}

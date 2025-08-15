/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:58:20 by emetel            #+#    #+#             */
/*   Updated: 2025/08/14 18:58:52 by emetel           ###   ########.fr       */
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
		char *new_option, t_sys *sys)
{
	int	i;

	(void)sys;
	i = 0;
	if (old_options)
	{
		while (old_options[i])
		{
			new_options[i] = old_options[i];
			i++;
		}
	}
	new_options[i] = gc_strdup(new_option, &(sys->garbage));
	if (!new_options[i])
		return (0);
	new_options[i + 1] = NULL;
	return (1);
}

void	handle_option_token(t_type *token, t_cmd_segment **current,
		t_cmd_segment **head, t_sys *sys)
{
	int		count;
	char	**new_options;

	if (!*current)
	{
		*current = gc_calloc(&(sys->garbage), sizeof(t_cmd_segment));
		if (*current)
			(*current)->sys = sys;
		if (!*head)
			*head = *current;
	}
	if (!*current || !token)
		return ;
	count = count_options((*current)->options);
	new_options = (char **)gc_malloc(&(sys->garbage), \
					sizeof(char *) * (count + 2));
	if (!new_options)
		return ;
	if (!fill_options_array(new_options, (*current)->options, token->str, sys))
	{
		return ;
	}
	(*current)->options = new_options;
}

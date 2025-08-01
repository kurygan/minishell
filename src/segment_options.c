/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:58:20 by emetel            #+#    #+#             */
/*   Updated: 2025/08/01 02:18:18 by mkettab          ###   ########.fr       */
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

	i = 0;
	if (old_options)
	{
		while (old_options[i])
		{
			new_options[i] = old_options[i];
			i++;
		}
	}
	new_options[i] = ft_strdup(new_option);
	if (!new_options[i])
		return (0);
	new_options[i + 1] = NULL;
	return (1);
}

void	handle_option_token(t_type *token, t_cmd_segment **current,
		t_cmd_segment **head, t_sys *sys)
{
	(void)sys;
	int		count;
	char	**new_options;

	if (!*current)
	{
		*current = ft_calloc(1, sizeof(t_cmd_segment));
		if (!*head)
			*head = *current;
	}
	if (!*current || !token)
		return ;
	count = count_options((*current)->options);
	new_options = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_options)
		return ;
	if (!fill_options_array(new_options, (*current)->options, token->str, sys))
	{
		free(new_options);
		return ;
	}
	if ((*current)->options)
		free((*current)->options);
	(*current)->options = new_options;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:58:20 by emetel            #+#    #+#             */
/*   Updated: 2025/05/29 01:59:15 by emetel           ###   ########.fr       */
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
		char *new_option)
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
		t_cmd_segment **head)
{
	int		count;
	char	**new_options;

	if (!*current)
	{
		*current = init_segment();
		if (!*head)
			*head = *current;
	}
	if (!*current || !token)
		return ;
	count = count_options((*current)->options);
	new_options = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_options)
		return ;
	if (!fill_options_array(new_options, (*current)->options, token->str))
	{
		free(new_options);
		return ;
	}
	if ((*current)->options)
		free((*current)->options);
	(*current)->options = new_options;
}

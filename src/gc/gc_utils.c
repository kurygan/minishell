/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:26:39 by mkettab           #+#    #+#             */
/*   Updated: 2025/06/24 23:00:08 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_gc	*gc_last(t_gc **gc)
{
	t_gc *last;
	
	if (!gc || !*gc)
		return (NULL);
	last = *gc;
	while (last->next)
		last = last->next;
	return (last);
}

void	gc_addback(t_gc **gc, t_gc *new)
{
	t_gc *temp;

	temp = gc_last(gc);
	if (!temp)
	{
		*gc = new;
		return ;
	}
	temp->next = new;
	new->prev = temp;
}

void	gc_free(t_gc **gc, t_gc_type type)
{
	t_gc *curr = *gc;
	t_gc *next;

	while (curr)
	{
		next = curr->next;
		if (curr->type == type || type == ALL)
		{
			if (curr->prev)
				curr->next->prev = curr->prev;
			if (curr->next)
				curr->prev->next = curr->next;
			if (!curr->prev)
				*gc = curr->next;
			free(curr->to_free);
			curr->to_free = NULL;
			free(curr);
		}
		curr = next;
	}
}
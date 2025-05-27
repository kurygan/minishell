/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:22:40 by mkettab           #+#    #+#             */
/*   Updated: 2025/05/27 22:28:31 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*gc_malloc(size_t size, t_gc **gc, t_gc_type type)
{
	void	*malloced;
	t_gc	*temp;
	
	malloced = malloc(size);
	if (!malloced)
		return (NULL);
	temp = malloc(sizeof(t_gc));
	if (!temp)
		return (free(malloced), NULL);
	temp->to_free = malloced;
	temp->type = type;
	temp->next = NULL;
	temp->prev = NULL;
	if (gc)
		gc_addback(gc, temp);
	else
		temp = gc;
}

void*	gc_calloc(size_t size, t_gc **gc, t_gc_type type)
{
	void	*malloced;
	malloced = gc_mall(size, gc, type);
	if (!malloced)
		return (NULL);
	return (malloced);
}
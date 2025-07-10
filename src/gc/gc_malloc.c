/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:22:40 by mkettab           #+#    #+#             */
/*   Updated: 2025/06/24 22:54:12 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		temp = *gc;
	return (malloced);
}

void*	gc_calloc(size_t size, t_gc **gc, t_gc_type type)
{
	void	*malloced;
	malloced = gc_malloc(size, gc, type);
	if (!malloced)
		return (NULL);
	ft_memset(malloced, 0, size);
	return (malloced);
}
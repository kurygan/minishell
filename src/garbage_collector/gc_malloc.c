/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:56:13 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/07 23:13:03 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/garbage.h"

void	*gc_malloc(gc **garbage, size_t size)
{
	gc		*temp;
	gc		*last;
	void	*mem;

	temp = malloc(sizeof(gc));
	if (!temp)
		return (NULL);
	temp->next = NULL;
	temp->prev = NULL;
	mem = malloc(sizeof(size));
	if (!mem)
		return (NULL);
	temp->mem = mem;
	if (!garbage)
		*garbage = temp;
	else
	{
		last = gc_getlast(garbage);
		last->next = temp;
		temp->prev = last;
	}
	return (mem);
}

void	*gc_calloc(gc **garbage, size_t size)
{
	void	*mem;
	mem = gc_malloc(garbage, size);
	if (!mem)
		return NULL;
	ft_memset(mem, 0, size);
	return mem;
}

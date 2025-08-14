/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:56:13 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/14 01:30:36 by mkettab          ###   ########.fr       */
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
	{
		gc_carbonize(garbage);
		ft_putstr_fd("Error: Malloc Failed", 2);
		exit(1);
	}
	temp->next = NULL;
	temp->prev = NULL;
	mem = malloc(size);
	if (!mem)
	{
		gc_carbonize(garbage);
		ft_putstr_fd("Error: Malloc Failed", 2);
		exit(1);
	}
	temp->mem = mem;
	if (!garbage || !*garbage)
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
	ft_memset(mem, 0, size);
	return mem;
}

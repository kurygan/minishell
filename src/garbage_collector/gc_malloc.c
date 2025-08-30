/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:56:13 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/30 14:28:52 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/garbage.h"

void	add_gc_tok(t_gc **garbage, t_gc *new)
{
	t_gc	*last;

	last = gc_getlast(garbage);
	last->next = new;
	new->prev = last;
}

void	*gc_malloc(t_gc **garbage, size_t size)
{
	t_gc		*temp;
	void		*mem;

	temp = malloc(sizeof(t_gc));
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
		add_gc_tok(garbage, temp);
	return (mem);
}

void	*gc_calloc(t_gc **garbage, size_t size)
{
	void	*mem;

	mem = gc_malloc(garbage, size);
	ft_memset(mem, 0, size);
	return (mem);
}

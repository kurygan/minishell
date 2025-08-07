/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:21:26 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/07 23:30:52 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/garbage.h"

void	gc_free(void *mem, gc **garbage)
{
	gc *temp;

	temp = *garbage;
	while (1)
	{
		if (!(temp->next) || mem == temp->mem)
			break;
		temp = temp->next;
	}
	if (!(temp->next))
		return;
	free(temp->mem);
	if (temp->prev)
		temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	free(temp);
}

void	gc_carbonize(gc	**garbage)
{
	gc *temp;
	gc *next;

	temp = *garbage;
	while (1)
	{
		next = temp->next;
		free(temp->mem);
		if (next)
			next->prev = NULL;
		free(temp);
		if (!(next))
			break;
		temp = next;
	}
}
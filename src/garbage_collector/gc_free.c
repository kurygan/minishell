/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:21:26 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/09 23:25:05 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/garbage.h"

void	gc_free(void *mem, gc **garbage)
{
	gc *temp;

	temp = *garbage;
	while (1)
	{
		if (!(temp->next) || temp->mem == mem)
			break;
		temp = temp->next;
	}
	if (!(temp->next) && temp->mem != mem)
		return (free(mem));
	free(temp->mem);
	if (temp->prev)
		temp->prev->next = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;
	free(temp);
}

void	gc_carbonize(gc	**garbage)
{
	gc *temp;
	gc *next;

	if (!garbage || !*garbage)
		return;
	temp = *garbage;
	while (temp)
	{
		next = temp->next;
		free(temp->mem);
		free(temp);
		temp = next;
	}
	*garbage = NULL;
}
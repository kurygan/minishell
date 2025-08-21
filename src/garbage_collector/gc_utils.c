/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:04:52 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/18 06:30:51 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/garbage.h"

t_gc	*gc_getlast(t_gc **garbage)
{
	t_gc	*temp;

	if (!garbage || !*garbage)
		return (NULL);
	temp = *garbage;
	while (1)
	{
		if (!(temp->next))
			break ;
		temp = temp->next;
	}
	return (temp);
}
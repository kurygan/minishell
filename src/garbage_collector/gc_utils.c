/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:04:52 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/07 23:22:58 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/garbage.h"

gc	*gc_getlast(gc **garbage)
{
	gc	*temp;

	temp = *garbage;
	while (1)
	{
		if (!(temp->next))
			break;
		temp = temp->next;
	}
	return (temp);
}
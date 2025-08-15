/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:04:52 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/14 18:23:42 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/garbage.h"

gc	*gc_getlast(gc **garbage)
{
	gc	*temp;

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

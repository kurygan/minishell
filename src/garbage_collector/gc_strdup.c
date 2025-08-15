/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:13:12 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/14 18:24:50 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/garbage.h"

char	*gc_strdup(const char *str, gc **garbage)
{
	char	*duped;

	duped = gc_malloc(garbage, sizeof(char) * (ft_strlen(str) + 1));
	if (!duped)
		return (NULL);
	duped = ft_strcpy(duped, str);
	return (duped);
}

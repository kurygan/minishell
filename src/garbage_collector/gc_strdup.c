/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:13:12 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/18 00:33:00 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/garbage.h"

char	*gc_strdup(const char *str, t_gc **garbage)
{
	char	*duped;

	duped = gc_malloc(garbage, sizeof(char) * (ft_strlen(str) + 1));
	duped = ft_strcpy(duped, str);
	return (duped);
}

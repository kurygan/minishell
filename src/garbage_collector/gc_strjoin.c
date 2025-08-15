/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:21:14 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/14 18:24:16 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/garbage.h"

char	*gc_strjoin(char *s1, char *s2, gc **garbage)
{
	size_t	j;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	joined = gc_malloc(garbage, sizeof(char) \
			* (ft_strlen(s1) + ft_strlen(s2) + 1));
	j = 0;
	if (!joined)
		return (NULL);
	while (*s1)
		joined[j++] = *s1++;
	while (*s2)
		joined[j++] = *s2++;
	joined[j] = 0;
	return (joined);
}

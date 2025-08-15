/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 00:47:29 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/14 18:22:59 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/garbage.h"

char	*gc_substr(char const *s, unsigned int start, size_t len, gc **garbage)
{
	unsigned int	i;
	char			*non_const_s;
	char			*subbed;

	if (!s)
		return (NULL);
	i = 0;
	non_const_s = (char *)s;
	if (ft_strlen(s) <= start)
		return (gc_strdup("", garbage));
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	subbed = gc_malloc(garbage, sizeof(char) * len + 1);
	if (!subbed)
		return (NULL);
	while (i < start && non_const_s[i])
		i++;
	ft_strlcpy(subbed, &non_const_s[i], len + 1);
	return (subbed);
}

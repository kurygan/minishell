/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tylerlover911 <tylerlover911@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 04:16:24 by mkettab           #+#    #+#             */
/*   Updated: 2025/03/20 01:13:43 by tylerlover9      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../libft.h"

char	*ft_strdup(const char *s1)
{
	char	*strduped;
	int		i;

	strduped = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!strduped)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		strduped[i] = s1[i];
		i++;
	}
	strduped[i] = 0;
	return (strduped);
}

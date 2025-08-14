/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 22:40:31 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/14 01:30:42 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/garbage.h"

static char	*ft_assign(int n, int len, int limits, char *dest)
{
	while (len > limits)
	{
		dest[len - 1] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (dest);
}

char	*gc_itoa(int n, gc **garbage)
{
	int		len;
	int		limits;
	char	*dest;

	len = ft_intlen(n);
	limits = 0;
	dest = gc_malloc(garbage, sizeof(char) * (len + 1));
	if (n == -2147483648)
	{
		ft_strlcpy(dest, "-2147483648", 12);
		return (dest);
	}
	if (n == 0)
		dest[0] = '0';
	if (n < 0)
	{
		dest[0] = '-';
		limits = 1;
		n = -n;
	}
	dest[len] = '\0';
	ft_assign(n, len, limits, dest);
	return (dest);
}

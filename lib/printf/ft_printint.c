/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tylerlover911 <tylerlover911@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:35:21 by mkettab           #+#    #+#             */
/*   Updated: 2025/03/21 00:52:14 by tylerlover9      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putint(long d)
{
	long	first;

	first = d;
	if (d < 0)
	{
		d = -d;
		ft_putchar('-');
	}
	if (d >= 10)
	{
		ft_putint(d / 10);
		ft_putint(d % 10);
	}
	if (d < 10)
		ft_putchar(d + '0');
	return (ft_intlen(first));
}

int	ft_putunsint(long d)
{
	if (d >= 10)
	{
		ft_putunsint(d / 10);
		ft_putunsint(d % 10);
	}
	if (d < 10)
		ft_putchar(d + '0');
	return (ft_intunslen(d));
}

int	ft_puthex(unsigned long c, int low)
{
	unsigned long	temp;
	char			*base;

	temp = c;
	if (low == 1)
		base = "0123456789abcdef";
	if (low == 0)
		base = "0123456789ABCDEF";
	if (c >= 16)
	{
		ft_puthex(c / 16, low);
		ft_puthex(c % 16, low);
	}
	if (c < 16)
		ft_putchar(base[c]);
	return (ft_inthexlen(temp));
}

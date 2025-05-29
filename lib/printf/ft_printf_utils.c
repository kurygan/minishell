/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:13:47 by mkettab           #+#    #+#             */
/*   Updated: 2025/05/29 14:47:21 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_intlen(long j)
{
	int	count;

	count = 0;
	if (j == 0)
		return (1);
	if (j < 0)
		count++;
	while (j != 0)
	{
		j /= 10;
		count++;
	}
	return (count);
}

int	ft_intunslen(long c)
{
	int	count;

	count = 0;
	if (c == 0)
		return (1);
	while (c != 0)
	{
		c /= 10;
		count++;
	}
	return (count);
}

int	ft_inthexlen(unsigned long c)
{
	int	count;

	count = 0;
	if (c == 0)
		return (1);
	while (c != 0)
	{
		c /= 16;
		count++;
	}
	return (count);
}

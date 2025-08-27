/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tylerlover911 <tylerlover911@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 00:56:30 by mkettab           #+#    #+#             */
/*   Updated: 2025/03/21 00:52:14 by tylerlover9      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putstr(char *str)
{
	int	count;

	if (!str)
		return (ft_putstr("(null)"));
	count = ft_strlen(str);
	while (*str)
		write(2, str++, 1);
	return (count);
}

int	ft_putchar(char c)
{
	write(2, &c, 1);
	return (1);
}

int	ft_putptr(void *ptr)
{
	uintptr_t	converted;

	converted = (uintptr_t) ptr;
	if (!ptr)
		return (ft_putstr("(nil)"));
	write(2, "0x", 2);
	return (ft_puthex((unsigned long)converted, 1) + 2);
}

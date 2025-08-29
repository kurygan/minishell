/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 02:35:44 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/29 20:12:08 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static bool	verif_overflow(bool negative, long long atolled, \
				unsigned char index)
{
	if (negative == false && (atolled > (LLONG_MAX - index) / 10))
		return (true);
	if (negative == true && (atolled > (LLONG_MAX - index + 1) / 10))
		return (true);
	return (false);
}

static void	parse_sign(char const **str, bool *negative)
{
	while ((**str >= 9 && **str <= 13) || **str == ' ')
		(*str)++;
	if (**str == '-')
	{
		*negative = true;
		(*str)++;
	}
	else if (**str == '+')
	{
		(*str)++;
	}
}

static long long	parse_digits(char const **str, bool negative, bool *error)
{
	long long		atolled;
	unsigned char	index;

	atolled = 0;
	while (**str >= '0' && **str <= '9')
	{
		index = **str - '0';
		*error = verif_overflow(negative, atolled, index);
		atolled = (atolled * 10) + index;
		(*str)++;
	}
	return (atolled);
}

long long	ft_atoll(char const *str, bool *error)
{
	long long		atolled;
	bool			negative;

	atolled = 0;
	negative = false;
	parse_sign(&str, &negative);
	atolled = parse_digits(&str, negative, error);
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str)
		return (*error = true, 0);
	if (negative)
		return (-atolled);
	return (atolled);
}

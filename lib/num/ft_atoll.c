/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 02:35:44 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/14 18:47:03 by emetel           ###   ########.fr       */
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
	printf("DEBUG: parse_sign start, str='%s'\n", *str);
	while ((**str >= 9 && **str <= 13) || **str == ' ')
		(*str)++;
	printf("DEBUG: after spaces, str='%s'\n", *str);
	if (**str == '-')
	{
		*negative = true;
		(*str)++;
		printf("DEBUG: found minus, str='%s'\n", *str);
	}
	else if (**str == '+')
	{
		(*str)++;
		printf("DEBUG: found plus, str='%s'\n", *str);
	}
	printf("DEBUG: parse_sign end, str='%s', negative=%d\n", *str, *negative);
}

static long long	parse_digits(char const **str, bool negative, bool *error)
{
	long long		atolled;
	unsigned char	index;

	atolled = 0;
	printf("DEBUG: parse_digits start, str='%s', negative=%d\n", *str, negative);
	while (**str >= '0' && **str <= '9')
	{
		index = **str - '0';
		*error = verif_overflow(negative, atolled, index);
		printf("DEBUG: digit=%c, index=%d, atolled=%lld, error=%d\n", **str, index, atolled, *error);
		atolled = (atolled * 10) + index;
		(*str)++;
	}
	printf("DEBUG: parse_digits end, str='%s', atolled=%lld, error=%d\n", *str, atolled, *error);
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
	printf("DEBUG: after parse_digits, str='%s', atolled=%lld, error=%d\n", str, atolled, *error);
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	printf("DEBUG: after spaces, str='%s'\n", str);
	if (*str)
		return (*error = true, 0);
	if (negative)
		return (-atolled);
	return (atolled);
}

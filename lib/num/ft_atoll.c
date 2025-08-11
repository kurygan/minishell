/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 02:35:44 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/11 03:13:12 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static bool	verif_overflow(bool negative, long long atolled, unsigned char index){
	if (negative == false && (atolled > (LLONG_MAX - index) / 10))
		return true;
	if (negative == true && (atolled > (-(LLONG_MIN + index)) / 10))
		return true;
	return false;
}

long long	ft_atoll(char const *str, bool *error)
{
	long long		atolled;
	bool			negative;
	unsigned char	index;

	atolled = 0;
	negative = false;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-'){
		negative = true;
		str++;
	}
	else if (*str == '+' && str[1] && ((str[1] <= 9 || str[1] >= 13) && str[1] != ' '))
		str++;
	while (*str >= '0' && *str <= '9'){
		index = *str - '0';
		*error = verif_overflow(negative, atolled, index);
		atolled = (atolled * 10) + index;
		str++;
	}
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str)
		return (*error = true, 0);
	if (negative)
		return (-atolled);
	return atolled;
}

int main(int argc, char const *argv[])
{
	bool error = false;
	long long test = ft_atoll(argv[1], &error);
	if (error)
		printf("numeric argument required\n");
	else
		printf("%lld\n", test);
	return 0;
}

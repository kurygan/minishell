/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tylerlover911 <tylerlover911@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 02:46:36 by mkettab           #+#    #+#             */
/*   Updated: 2025/03/20 01:13:43 by tylerlover9      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../libft.h"

static char	*verif_chars(
	char *haystack, char *needle,
	size_t len_needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i <= len - len_needle && haystack[i])
	{
		while (j <= len_needle)
		{
			if (needle[j] == 0)
				return (haystack + i);
			if (haystack[j + i] != needle[j])
				break ;
			j++;
		}
		i++;
		j = 0;
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*char_haystack;
	char	*char_needle;
	size_t	len_haystack;
	size_t	len_needle;
	char	*result;

	if ((char)*needle == 0)
		return ((char *)haystack);
	if (!len)
		return (NULL);
	len_haystack = ft_strlen(haystack);
	len_needle = ft_strlen(needle);
	char_haystack = (char *)haystack;
	char_needle = (char *)needle;
	if (len_needle > len_haystack || len < len_needle)
		return (NULL);
	result = verif_chars(char_haystack, char_needle, len_needle, len);
	return (result);
}

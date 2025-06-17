/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 23:04:45 by mkettab           #+#    #+#             */
/*   Updated: 2025/06/10 21:59:25 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*gc_strdup(char *str, t_gc **gc, t_gc_type type)
{
	char	*duped;

	duped = gc_malloc(sizeof(char) * ft_strlen(str), gc, type);
	if (!duped)
		return (NULL);
	duped = ft_strcpy(duped, str);
	return (duped);
}
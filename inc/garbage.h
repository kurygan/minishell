/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:52:49 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/08 00:49:33 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_H
# define GARBAGE_H

# include "minishell.h"

typedef struct _gc
{
	void	*mem;
	struct _gc	*next;
	struct _gc	*prev;
}	gc;

gc	*gc_getlast(gc **garbage);
void	*gc_malloc(gc **garbage, size_t size);
void	*gc_calloc(gc **garbage, size_t size);
char	*gc_strdup(const char *str, gc **garbage);
void	gc_carbonize(gc **garbage);
char	*gc_substr(char const *s, unsigned int start, size_t len, gc **garbage);

#endif
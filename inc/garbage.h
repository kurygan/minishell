/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:52:49 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/14 18:45:04 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_H
# define GARBAGE_H

# include "minishell.h"

typedef struct _gc
{
	void		*mem;
	struct _gc	*next;
	struct _gc	*prev;
}	gc;

gc		*gc_getlast(gc **garbage);
void	*gc_malloc(gc **garbage, size_t size);
void	*gc_calloc(gc **garbage, size_t size);
char	*gc_strdup(const char *str, gc **garbage);
void	gc_carbonize(gc **garbage);
char	*gc_substr(char const *s, unsigned int start, size_t len, \
			gc **garbage);
void	gc_free(void *mem, gc **garbage);
char	*gc_strjoin(char *s1, char *s2, gc **garbage);
char	*gc_itoa(int n, gc **garbage);

#endif
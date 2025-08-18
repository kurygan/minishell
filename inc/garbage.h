/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:52:49 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/17 02:13:51 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_H
# define GARBAGE_H

# include "minishell.h"

typedef struct s_gc
{
	void	*mem;
	struct s_gc	*next;
	struct s_gc	*prev;
}	t_gc;

t_gc	*gc_getlast(t_gc **garbage);
void	*gc_malloc(t_gc **garbage, size_t size);
void	*gc_calloc(t_gc **garbage, size_t size);
char	*gc_strdup(const char *str, t_gc **garbage);
void	gc_carbonize(t_gc **garbage);
char	*gc_substr(char const *s, unsigned int start, size_t len, t_gc **garbage);
void	gc_free(void *mem, t_gc **garbage);
char	*gc_strjoin(char *s1, char *s2, t_gc **garbage);
char	*gc_itoa(int n, t_gc **garbage);

#endif
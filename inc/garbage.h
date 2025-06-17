/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:04:46 by mkettab           #+#    #+#             */
/*   Updated: 2025/06/10 22:28:05 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_H
# define GARBAGE_H

# include "minishell.h"

typedef enum s_gc_type
{
	EXEC,
	PARSING,
	ENV,
	BUILTIN,
	REDIR,
	OTHER,
	ALL
}	t_gc_type;

typedef struct s_gc
{
	void	*to_free;
	t_gc_type	type;
	struct s_gc	*next;
	struct s_gc	*prev;
}	t_gc;

void	gc_addback(t_gc **gc, t_gc *new);
void	*gc_malloc(size_t size, t_gc **gc, t_gc_type type);
void	gc_free(t_gc **gc, t_gc_type type);
t_gc	*gc_last(t_gc **gc);
void*	gc_calloc(size_t size, t_gc **gc, t_gc_type type);
char	*gc_strdup(char *str, t_gc **gc, t_gc_type type);

#endif
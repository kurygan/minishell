/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:04:46 by mkettab           #+#    #+#             */
/*   Updated: 2025/05/21 03:05:59 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_H
# define GARBAGE_H

# include "minishell.h"

typedef enum s_gc_type
{
	EXEC,
	LEXER,
	PARSING,
	ENV,
	BUILTIN,
	REDIR,
	OTHER
}	t_gc_type;

typedef struct s_gc
{
	void	*to_free;
	t_gc_type	type;
	struct s_gc	*next;
	struct s_gc	*prev;
}	t_gc;

void	gc_addback(t_gc **gc, t_gc *new);

#endif
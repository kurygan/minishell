/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:20:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 14:58:25 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_type	*create_new_token(char *str, t_token token, t_sys *sys)
{
	t_type	*new;

	new = gc_malloc(&(sys->garbage), sizeof(t_type));
	ft_memset(new, 0, sizeof(t_type));
	new->str = gc_strdup(str, &(sys->garbage));
	new->token = token;
	new->sys = sys;
	return (new);
}

static t_type	*find_last_token(t_type *list)
{
	t_type	*tmp;

	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_type	*add_token(t_type *list, char *str, t_token token, t_sys *sys)
{
	t_type	*new;
	t_type	*last;

	new = create_new_token(str, token, sys);
	if (!list)
		return (new);
	last = find_last_token(list);
	last->next = new;
	new->prev = last;
	new->next = NULL;
	return (list);
}

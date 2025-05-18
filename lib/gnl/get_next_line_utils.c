/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:24:41 by mkettab           #+#    #+#             */
/*   Updated: 2025/03/25 20:00:49 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_getlast(t_list *list)
{
	t_list	*last;

	last = list;
	while (last && last->next)
		last = last->next;
	return (last);
}

int	ft_foundline(t_list *list)
{
	t_list	*current;
	int		i;

	if (!list)
		return (1);
	current = ft_getlast(list);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

void	line_gen(char **str, t_list *buf)
{
	int	i;
	int	len;

	len = 0;
	while (buf)
	{
		i = 0;
		while (buf->content[i])
		{
			if (buf->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		buf = buf->next;
	}
	*str = malloc(sizeof(char) * (len + 1));
}

void	lst_free(t_list *lst)
{
	t_list	*curr;
	t_list	*next;

	curr = lst;
	while (curr)
	{
		free(curr->content);
		next = curr->next;
		free(curr);
		curr = next;
	}
}

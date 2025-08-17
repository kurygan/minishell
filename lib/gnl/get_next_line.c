/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:24:39 by mkettab           #+#    #+#             */
/*   Updated: 2025/03/25 20:00:21 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*get_next_line(int fd)
{
	static t_list	*buf;
	char			*fin_line;
	int				error;

	buf = NULL;
	fin_line = NULL;
	error = read_and_stock(&buf, fd);
	if (0 == error)
		return (NULL);
	if (-1 == error)
		return (lst_free(buf), buf = NULL, NULL);
	get_line_appart(buf, &fin_line);
	lst_clean(&buf);
	if (!(fin_line[0]))
	{
		lst_free(buf);
		buf = NULL;
		free(fin_line);
		return (NULL);
	}
	return (fin_line);
}

int	read_and_stock(t_list **buf, int fd)
{
	char	*str;
	int		readed;

	readed = 1;
	while (ft_foundline(*buf) && readed > 0)
	{
		str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!str)
			return (0);
		readed = (int)read(fd, str, BUFFER_SIZE);
		if (-1 == readed)
			return (free(str), -1);
		if (!buf && !readed)
			return (free(str), 0);
		str[readed] = 0;
		stock_add(str, buf, readed);
		free(str);
	}
	return (1);
}

void	stock_add(char *str, t_list **buf, int readed)
{
	int		i;
	t_list	*last;
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new->next = NULL;
	new->content = malloc(sizeof(char) * (readed + 1));
	if (new->content == NULL)
		return ;
	i = 0;
	while (str[i] && i < readed)
	{
		new->content[i] = str[i];
		i++;
	}
	new->content[i] = 0;
	if (!*buf)
	{
		*buf = new;
		return ;
	}
	last = ft_getlast(*buf);
	last->next = new;
}

void	get_line_appart(t_list *buf, char **str)
{
	int	i;
	int	j;

	if (!buf)
		return ;
	line_gen(str, buf);
	if (!(*str))
		return ;
	j = 0;
	while (buf)
	{
		i = 0;
		while (buf->content[i])
		{
			if (buf->content[i] == '\n')
			{
				(*str)[j++] = buf->content[i];
				break ;
			}
			(*str)[j++] = buf->content[i++];
		}
		buf = buf->next;
	}
	(*str)[j] = 0;
}

void	lst_clean(t_list **buf)
{
	t_list	*get_last;
	t_list	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list));
	if (!buf || !clean_node)
		return ;
	clean_node->next = NULL;
	get_last = ft_getlast(*buf);
	i = 0;
	while (get_last->content[i] && get_last->content[i] != '\n')
		i++;
	if (get_last->content && get_last->content[i] == '\n')
		i++;
	clean_node->content = malloc(sizeof(char) * ((ft_strlen(get_last->content)
					- i) + 1));
	if (!(clean_node->content))
		return ;
	j = 0;
	while (get_last->content[i])
		clean_node->content[j++] = get_last->content[i++];
	clean_node->content[j] = 0;
	lst_free(*buf);
	*buf = clean_node;
}

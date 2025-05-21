/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:01:33 by mkettab           #+#    #+#             */
/*   Updated: 2025/05/21 02:15:56 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_type	*handle_line(char *line, char **env)
{
	(void)env;
	return (tokenize(line));
}

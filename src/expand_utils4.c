/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:40:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 15:42:06 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*expand_exit_status_var(int *i, t_sys *sys)
{
	char	*value;
	char	*result;

	value = gc_itoa(sys->exit_status, &(sys->garbage));
	result = gc_strdup(value, &(sys->garbage));
	*i += 2;
	return (result);
}

char	*extract_var_content(char *content, int *i, int start, t_gc **garbage)
{
	char	*temp;

	temp = gc_substr(content, *i + 1, start - *i - 1, garbage);
	*i = start;
	return (temp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:00:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/29 20:35:19 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_redirection_token(t_token token)
{
	return (token == REDIR_IN || token == REDIR_OUT \
		|| token == REDIR_APPEND || token == REDIR_HEREDOC);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:00:00 by emetel            #+#    #+#             */
/*   Updated: 2025/08/27 19:07:04 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_redirection_token(t_token token)
{
	return (token == REDIR_IN || token == REDIR_OUT \
		|| token == REDIR_APPEND || token == REDIR_HEREDOC \
		|| token == REDIR_TARGET);
}

bool	should_become_args(t_type *tmp)
{
	return (tmp->prev && !(tmp->prev->token == CMD || tmp->prev->token == PIPE \
		|| !is_redirection_token(tmp->token)));
}

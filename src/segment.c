/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:34:58 by emetel            #+#    #+#             */
/*   Updated: 2025/05/22 02:18:34 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	add_arg_to_segment(t_cmd_segment *seg, char *arg)
{
	int		len;
	char	**new_args;
	int		i;

	len = 0;
	if (seg->args)
	{
		while (seg->args[len])
			len++;
	}
	new_args = ft_calloc(len + 2, sizeof(char *));
	if (!new_args)
		return ;
	i = 0;
	while (i < len)
	{
		new_args[i] = seg->args[i];
		i++;
	}
	new_args[len] = ft_strdup(arg);
	new_args[len + 1] = NULL;
	free(seg->args);
	seg->args = new_args;
}

static void	handle_redirection_token(t_cmd_segment *seg, t_type **tokens)
{
	t_token	type;
	char	*file;

	type = (*tokens)->token;
	if ((*tokens)->next)
	{
		file = (*tokens)->next->str;
		if (type == IN)
			seg->infile = ft_strdup(file);
		else if (type == HEREDOC)
			seg->heredoc = ft_strdup(file);
		else if (type == TRUNCATE)
		{
			seg->outfile = ft_strdup(file);
			seg->append_mode = 0;
		}
		else if (type == APPEND)
		{
			seg->outfile = ft_strdup(file);
			seg->append_mode = 1;
		}
		*tokens = (*tokens)->next;
	}
}

static t_cmd_segment	*create_segment(t_type **tokens)
{
	t_cmd_segment	*seg;

	seg = ft_calloc(1, sizeof(t_cmd_segment));
	if (!seg)
		return (NULL);
	while (*tokens && (*tokens)->token != PIPE)
	{
		if ((*tokens)->token == CMD && !seg->cmd)
			seg->cmd = ft_strdup((*tokens)->str);
		else if ((*tokens)->token == ARGS)
			add_arg_to_segment(seg, (*tokens)->str);
		else if ((*tokens)->token >= IN && (*tokens)->token <= APPEND)
			handle_redirection_token(seg, tokens);
		*tokens = (*tokens)->next;
	}
	return (seg);
}

t_cmd_segment	*convert_tokens(t_type *tokens)
{
	t_cmd_segment	*segments;
	t_cmd_segment	*last;
	t_cmd_segment	*new;

	segments = NULL;
	last = NULL;
	while (tokens)
	{
		new = create_segment(&tokens);
		if (!segments)
			segments = new;
		else
			last->next = new;
		last = new;
		if (tokens && tokens->token == PIPE)
			tokens = tokens->next;
	}
	return (segments);
}

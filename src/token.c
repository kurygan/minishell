/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 02:42:19 by emetel            #+#    #+#             */
/*   Updated: 2025/05/22 02:10:00 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	assign_cmd_and_args(t_type *token_lst)
{
	t_type	*tmp;
	int		expect_cmd;

	tmp = token_lst;
	expect_cmd = 1;
	while (tmp)
	{
		if (tmp->token == CMD)
		{
			if (expect_cmd)
				expect_cmd = 0;
			else
				tmp->token = ARGS;
		}
		else if (tmp->token == PIPE)
			expect_cmd = 1;
		tmp = tmp->next;
	}
}

t_type	*tokenize(char *line)
{
	int		i;
	t_type	*token_lst;

	i = 0;
	token_lst = NULL;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else if (line[i] == '|')
			handle_pipe(line, &i, &token_lst);
		else if (line[i] == '<' || line[i] == '>')
			handle_redirection(line, &i, &token_lst);
		else if (line[i] == '\'' || line[i] == '\"')
			handle_quote(line, &i, &token_lst, line[i]);
		else
			handle_word(line, &i, &token_lst);
	}
	assign_cmd_and_args(token_lst);
	return (token_lst);
}

t_type	*add_token(t_type *list, char *str, t_token token)
{
	t_type	*new;
	t_type	*tmp;

	new = ft_calloc(1, sizeof(t_type));
	new->str = ft_strdup(str);
	new->token = token;
	if (!list)
		return (new);
	tmp = list;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
	new->prev = tmp;
	return (list);
}

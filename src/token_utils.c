/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:08:22 by emetel            #+#    #+#             */
/*   Updated: 2025/08/22 20:29:19 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_pipe(int *i, t_type **lst, t_sys *sys)
{
	*lst = add_token(*lst, "|", PIPE, sys);
	(*i)++;
}

void	handle_quote(char *line, int *i, t_type **lst, t_sys *sys)
{
	int		start;
	char	*word;
	char	quote;
	t_token	token_type;

	quote = line[*i];
	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
	{
		*i = start;
		return ;
	}
	word = gc_substr(line, start, (*i - start) + 1, &(sys->garbage));
	if (quote == '\'')
		token_type = SINGLE_QUOTE;
	else
		token_type = DOUBLE_QUOTE;
	*lst = add_token(*lst, word, token_type, sys);
	(*i)++;
}

void	handle_word(char *line, int *i, t_type **lst, t_sys *sys)
{
	int		start;
	char	*word;
	t_token	token_type;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>'
		&& line[*i] != '\'' && line[*i] != '\"')
		(*i)++;
	word = gc_substr(line, start, *i - start, &(sys->garbage));
	if (!word)
		return ;
	if (!*lst || (*lst)->token == PIPE)
		token_type = CMD;
	else
		token_type = ARGS;
	*lst = add_token(*lst, word, token_type, sys);
}

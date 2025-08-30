/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:08:22 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 11:53:53 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	check_unclosed_quotes(char *line)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i];
			i++;
			while (line[i] && line[i] != quote)
				i++;
			if (!line[i])
				return (true);
		}
		i++;
	}
	return (false);
}

void	handle_pipe(int *i, t_type **lst, t_sys *sys)
{
	*lst = add_token(*lst, "|", PIPE, sys);
	(*i)++;
}

void	handle_quote(char *line, int *i, t_type **lst, t_sys *sys)
{
	int		start;
	char	*word[2];
	char	quote;
	t_token	token_type;

	quote = line[*i];
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
	{
		*i = start;
		return ;
	}
	word[0] = gc_substr(line, start, *i - start, &(sys->garbage));
	(*i)++;
	start = *i;
	// Only concatenate if there's no space immediately after the quotes
	if (line[start] != ' ' && line[start] != '\t')
	{
		while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
			&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
			(*i)++;
		word[1] = gc_substr(line, start, *i - start, &(sys->garbage));
		word[0] = gc_strjoin(word[0], word[1], &(sys->garbage));
	}
	if (quote == '\'')
		token_type = SINGLE_QUOTE;
	else
		token_type = DOUBLE_QUOTE;
	*lst = add_token(*lst, word[0], token_type, sys);
}

char	*extract_quoted_arg(char *line, int *i, char quote, t_sys *sys)
{
	int		start;
	char	*target[2];
	char	*result;

	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	target[0] = gc_substr(line, start, *i - start + 1, &sys->garbage);
	(*i)++;
	start = *i;
	// Only concatenate if there's no space immediately after the quotes
	if (line[start] != ' ' && line[start] != '\t')
	{
		while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
			&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
			(*i)++;
		if (start < *i)
		{
			target[1] = gc_substr(line, start, *i - start, &(sys->garbage));
			result = gc_strjoin(target[0], target[1], &(sys->garbage));
		}
		else
			result = target[0];
		if (line[*i])
			(*i)++;
	}
	else
		result = target[0];
	return (result);
}

void	handle_word(char *line, int *i, t_type **lst, t_sys *sys)
{
	int		start;
	char	*word;
	t_token	token_type;
	int		in_assignment;

	start = *i;
	in_assignment = 0;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
	{
		if (line[*i] == '=')
			in_assignment = 1;
		if (in_assignment && (line[*i] == '\'' || line[*i] == '\"'))
		{
			(*i)++;
			while (line[*i] && line[*i] != line[*i - 1])
				(*i)++;
			if (line[*i])
				(*i)++;
		}
		else
			(*i)++;
	}
	word = gc_substr(line, start, *i - start, &(sys->garbage));
	if (!word)
		return ;
	if (!*lst || (*lst)->token == PIPE || is_redirection_token((*lst)->token))
		token_type = CMD;
	else
		token_type = ARGS;
	*lst = add_token(*lst, word, token_type, sys);
}

t_type	*add_token(t_type *list, char *str, t_token token, t_sys *sys)
{
	t_type	*new;
	t_type	*tmp;

	new = gc_malloc(&(sys->garbage), sizeof(t_type));
	ft_memset(new, 0, sizeof(t_type));
	new->str = gc_strdup(str, &(sys->garbage));
	new->token = token;
	new->sys = sys;
	if (!list)
		return (new);
	tmp = list;
	while (1)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	tmp->next = new;
	new->prev = tmp;
	new->next = NULL;
	return (list);
}

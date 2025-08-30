/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:08:22 by emetel            #+#    #+#             */
/*   Updated: 2025/08/30 14:58:25 by emetel           ###   ########.fr       */
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

static void	skip_quoted_in_assignment(char *line, int *i)
{
	(*i)++;
	while (line[*i] && line[*i] != line[*i - 1])
		(*i)++;
	if (line[*i])
		(*i)++;
}

static void	extract_word_with_assignment(char *line, int *i)
{
	int	in_assignment;

	in_assignment = 0;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
	{
		if (line[*i] == '=')
			in_assignment = 1;
		if (in_assignment && (line[*i] == '\'' || line[*i] == '\"'))
			skip_quoted_in_assignment(line, i);
		else
			(*i)++;
	}
}

void	handle_word(char *line, int *i, t_type **lst, t_sys *sys)
{
	int		start;
	char	*word;
	t_token	token_type;

	start = *i;
	extract_word_with_assignment(line, i);
	word = gc_substr(line, start, *i - start, &(sys->garbage));
	if (!word)
		return ;
	if (!*lst || (*lst)->token == PIPE || is_redirection_token((*lst)->token))
		token_type = CMD;
	else
		token_type = ARGS;
	*lst = add_token(*lst, word, token_type, sys);
}

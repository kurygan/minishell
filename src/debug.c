/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 02:25:51 by emetel            #+#    #+#             */
/*   Updated: 2025/08/03 18:02:32 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	debug_print_segments(t_cmd_segment *seg)
{
	int	i;
	int	j;

	if (!seg)
	{
		printf("\n┌─────────────────────────────┐\n");
		printf("│        SEGMENTS: NONE       │\n");
		printf("└─────────────────────────────┘\n\n");
		return ;
	}
	printf("\n┌─────────────────────────────┐\n");
	printf("│         SEGMENTS           │\n");
	printf("└─────────────────────────────┘\n");
	i = 1;
	while (seg)
	{
		printf("┌─ Segment %d %s\n", i++, seg->next ? "├────────────────"
			: "└────────────────");
		printf("│  Command  : %s\n", seg->cmd ? seg->cmd : "(null)");
		printf("│  Options  : ");
		if (!seg->options)
		{
			printf("(null)\n");
		}
		else
		{
			printf("[");
			j = 0;
			while (seg->options[j])
			{
				printf("\"%s\"", seg->options[j]);
				if (seg->options[j + 1])
					printf(", ");
				j++;
			}
			printf("]\n");
		}
		printf("│  Args     : ");
		if (!seg->args)
		{
			printf("(null)\n");
		}
		else
		{
			printf("[");
			j = 0;
			while (seg->args[j])
			{
				printf("\"%s\"", seg->args[j]);
				if (seg->args[j + 1])
					printf(", ");
				j++;
			}
			printf("]\n");
		}
		printf("│  Infile   : %s\n", seg->infile ? seg->infile : "(null)");
		printf("│  Heredoc  : %s\n", seg->heredoc ? seg->heredoc : "(null)");
		printf("│  Outfile  : %s\n", seg->outfile ? seg->outfile : "(null)");
		printf("│  Append   : %s\n", seg->append_mode ? "YES" : "NO");
		printf("│\n");
		seg = seg->next;
	}
	printf("\n");
}

void	free_segments(t_cmd_segment *segments)
{
	t_cmd_segment	*tmp;
	int				i;

	while (segments)
	{
		tmp = segments->next;
		free(segments->cmd);
		if (segments->args)
		{
			i = 0;
			while (segments->args[i])
			{
				free(segments->args[i]);
				i++;
			}
			free(segments->args);
		}
		if (segments->options)
		{
			i = 0;
			while (segments->options[i])
			{
				free(segments->options[i]);
				i++;
			}
			free(segments->options);
		}
		free(segments->infile);
		free(segments->outfile);
		free(segments->heredoc);
		free(segments);
		segments = tmp;
	}
}

void	free_token_list(t_type *lst)
{
	t_type	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->str);
		free(lst);
		lst = tmp;
	}
}

void	debug_print_tokens(t_type *tokens)
{
	t_type		*token;
	int			i;
	const char	*token_types[] = {
		"CMD", "ARGS", "PIPE",
		"REDIR_IN", "REDIR_OUT", "REDIR_APPEND", "REDIR_HEREDOC",
		"REDIR_TARGET", "OPTIONS", "ERROR"
	};

	if (!tokens)
	{
		printf("\n┌─────────────────────────────┐\n");
		printf("│         TOKENS: NONE        │\n");
		printf("└─────────────────────────────┘\n\n");
		return ;
	}
	printf("\n┌─────────────────────────────┐\n");
	printf("│           TOKENS           │\n");
	printf("└─────────────────────────────┘\n");
	token = tokens;
	i = 1;
	while (token)
	{
		printf("├─ Token %3d: ", i++);
		if (token->token >= 0 && token->token <= 9)
			printf("%-13s", token_types[token->token]);
		else
			printf("%-13s", "UNKNOWN");
		printf(" │ '%s'\n", token->str ? token->str : "(null)");
		token = token->next;
	}
	printf("└─────────────────────────────┘\n\n");
}

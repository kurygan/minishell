/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 02:25:51 by emetel            #+#    #+#             */
/*   Updated: 2025/08/08 01:15:37 by mkettab          ###   ########.fr       */
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
	printf("│         SEGMENTS            │\n");
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
	// Memory is managed by garbage collector - no manual freeing needed
	(void)segments;
}

void	free_token_list(t_type *lst)
{
	// Memory is managed by garbage collector - no manual freeing needed
	(void)lst;
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
	printf("│           TOKENS            │\n");
	printf("└─────────────────────────────┘\n");
	token = tokens;
	i = 1;
	while (1)
	{
		printf("├─ Token %3d: ", i++);
		if (token->token >= 0 && token->token <= 9)
			printf("%-13s", token_types[token->token]);
		else
			printf("%-13s", "UNKNOWN");
		printf(" │ '%s'\n", token->str ? token->str : "(null)");
		if (!(token->next))
			break;
		token = token->next;
	}
	printf("└─────────────────────────────┘\n\n");
}

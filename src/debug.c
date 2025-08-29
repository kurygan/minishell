/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:08:22 by emetel            #+#    #+#             */
/*   Updated: 2025/08/22 20:29:19 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	print_segment_header(t_cmd_segment *seg, int i)
{
	if (seg->next)
		printf("┌─ Segment %d ├────────────────\n", i);
	else
		printf("┌─ Segment %d └────────────────\n", i);
}

static void	print_segment_args(char **args)
{
	int	j;

	printf("│  Args     : ");
	if (!args)
	{
		printf("(null)\n");
		return ;
	}
	printf("[");
	j = 0;
	while (args[j])
	{
		printf("\"%s\"", args[j]);
		if (args[j + 1])
			printf(", ");
		j++;
	}
	printf("]\n");
}

static void	print_segment_info(t_cmd_segment *seg)
{
	printf("│  Command  : ");
	if (seg->cmd)
		printf("%s\n", seg->cmd);
	else
		printf("(null)\n");
	print_segment_args(seg->args);
	printf("│  Infile   : ");
	if (seg->infile)
		printf("%s\n", seg->infile);
	else
		printf("(null)\n");
	printf("│  Heredoc  : ");
	if (seg->heredoc)
		printf("%s\n", seg->heredoc);
	else
		printf("(null)\n");
	printf("│  Outfile  : ");
	if (seg->outfiles)
		printf("%s\n", seg->outfiles->str);
	else
		printf("(null)\n");
}

void	debug_print_segments(t_cmd_segment *segments)
{
	t_cmd_segment	*seg;
	int				i;

	if (!segments)
	{
		printf("\n┌─────────────────────────────┐\n");
		printf("│       SEGMENTS: NONE       │\n");
		printf("└─────────────────────────────┘\n\n");
		return ;
	}
	printf("\n┌─────────────────────────────┐\n");
	printf("│         SEGMENTS            │\n");
	printf("└─────────────────────────────┘\n");
	seg = segments;
	i = 1;
	while (seg)
	{
		print_segment_header(seg, i++);
		print_segment_info(seg);
		seg = seg->next;
	}
	printf("\n");
}


//void	free_segments(t_cmd_segment *segments)
//{
//	// Memory is managed by garbage collector - no manual freeing needed
//	(void)segments;
//}

//void	free_token_list(t_type *lst)
//{
//	// Memory is managed by garbage collector - no manual freeing needed
//	(void)lst;
//}

void	debug_print_tokens(t_type *tokens)
{
	t_type		*token;
	int			i;
	const char	*token_types[] = {
		"CMD", "ARGS", "PIPE",
		"REDIR_IN", "REDIR_OUT", "REDIR_APPEND", "REDIR_HEREDOC",
		"REDIR_TARGET", "ERROR"
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
		if (token->token >= 0 && token->token <= 8)
			printf("%-13s", token_types[token->token]);
		else
			printf("%-13s", "UNKNOWN");
		printf(" │ '%s'\n", token->str ? token->str : "(null)");
		if (!(token->next))
			break ;
		token = token->next;
	}
	printf("└─────────────────────────────┘\n\n");
}

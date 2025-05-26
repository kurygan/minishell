#include "../inc/minishell.h"

void	debug_print_segments(t_cmd_segment *seg)
{
	int	i;
	int	seg_index;

	seg_index = 1;
	while (seg)
	{
		printf("========== Segment %d ==========\n", seg_index);
		printf("CMD        : %s\n", seg->cmd ? seg->cmd : "(null)");

		printf("ARGS       : ");
		if (seg->args)
		{
			i = 0;
			while (seg->args[i])
			{
				printf("[%s] ", seg->args[i]);
				i++;
			}
			printf("\n");
		}
		else
			printf("(none)\n");

		printf("INFILE     : %s\n", seg->infile ? seg->infile : "(null)");
		printf("HEREDOC    : %s\n", seg->heredoc ? seg->heredoc : "(null)");
		printf("OUTFILE    : %s\n", seg->outfile ? seg->outfile : "(null)");
		printf("APPEND     : %s\n", seg->append_mode ? "YES" : "NO");
		printf("================================\n\n");

		seg = seg->next;
		seg_index++;
	}
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

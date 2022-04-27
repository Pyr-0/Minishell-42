/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:21:59 by shaas             #+#    #+#             */
/*   Updated: 2022/04/27 18:35:41 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	read_heredoc_fail_exit(int *heredoc_pp, t_parser_block *parser_blocks,
			t_exec_block *exec_blocks)
{
	close(heredoc_pp[PIPE_READ]);
	close(heredoc_pp[PIPE_WRITE]);
	free(heredoc_pp);
	redir_creator_fail_exit2(parser_blocks, exec_blocks);
}

bool	check_if_last_input_is_heredoc(t_parser_block *i_parser)
{
	t_redir	*i_redir;
	bool	last_input_is_heredoc;

	i_redir = i_parser->redir;
	last_input_is_heredoc = false;
	while (i_redir != NULL)
	{
		if (i_redir->e_redir_type == REDIR_INPUT_HEREDOC)
			last_input_is_heredoc = true;
		if (i_redir->e_redir_type == REDIR_INPUT_FILE)
			last_input_is_heredoc = false;
		i_redir = i_redir->next;
	}
	return (last_input_is_heredoc);
}

int	init_i_exec_with_heredoc(int *heredoc_pp,
				t_exec_block *i_exec, t_parser_block *i_parser)
{
	int		heredoc_pp_out;
	bool	last_input_is_heredoc;

	last_input_is_heredoc = check_if_last_input_is_heredoc(i_parser);
	if (last_input_is_heredoc == true)
	{
		i_exec->heredoc_pp_in = heredoc_pp[PIPE_WRITE];
		heredoc_pp_out = heredoc_pp[PIPE_READ];
		free(heredoc_pp);
		return (heredoc_pp_out);
	}
	else
	{
		if (heredoc_pp[PIPE_READ] != 0)
			close(heredoc_pp[PIPE_READ]);
		if (heredoc_pp[PIPE_WRITE] != 0)
			close(heredoc_pp[PIPE_WRITE]);
		free(heredoc_pp);
		return (-1);
	}
}

void	read_heredoc(int *heredoc_pp,
			t_redir *i_redir, t_exec_block *exec_blocks,
			t_parser_block *parser_blocks)
{
	char	*line_read;
	char	*line_with_newline;

	if (pipe(heredoc_pp) == -1)
		redir_creator_fail_exit2(parser_blocks, exec_blocks);
	while (true)
	{
		line_read = readline("\e[1;91mheredoc_>\e[46m\e[0m");
		if (line_read == NULL)
			read_heredoc_fail_exit(heredoc_pp, parser_blocks, exec_blocks);
		if (ft_strcmp(line_read, i_redir->id) == 0)// we need to check the logic of the strcmp because it works with any part of the delimiter!
		{
			free (line_read);
			return ;
		}
		line_with_newline = ft_strjoin(line_read, "\n");
		if (line_with_newline == NULL)
			read_heredoc_fail_exit(heredoc_pp, parser_blocks, exec_blocks);
		write(heredoc_pp[PIPE_WRITE], line_with_newline,
			ft_strlen(line_with_newline));
		free(line_read);
		free(line_with_newline);
	}
}

int	handle_heredocs(t_exec_block *i_exec,
				t_parser_block *i_parser, t_exec_block *exec_blocks,
					t_parser_block *parser_blocks)
{
	t_redir	*i_redir;
	int		*heredoc_pp;

	heredoc_pp = ft_calloc(2, sizeof(int));
	if (heredoc_pp == NULL)
		redir_creator_fail_exit2(parser_blocks, exec_blocks);
	i_redir = i_parser->redir;
	while (i_redir != NULL)
	{
		if (i_redir->e_redir_type == REDIR_INPUT_HEREDOC)
		{
			if (heredoc_pp[PIPE_READ] != 0)
			{
				close(heredoc_pp[PIPE_WRITE]);
				close(heredoc_pp[PIPE_READ]);
			}
			read_heredoc(heredoc_pp, i_redir, exec_blocks, parser_blocks);
		}
		i_redir = i_redir->next;
	}
	return (init_i_exec_with_heredoc(heredoc_pp, i_exec, i_parser));
}

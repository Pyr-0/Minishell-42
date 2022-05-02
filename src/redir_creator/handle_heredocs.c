/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:21:59 by shaas             #+#    #+#             */
/*   Updated: 2022/05/02 22:38:41 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_i_exec_with_heredoc(int *heredoc_pp, t_parser_block *i_parser)
{
	int		heredoc_pp_out;
	bool	last_input_is_heredoc;

	last_input_is_heredoc = check_if_last_input_is_heredoc(i_parser);
	if (last_input_is_heredoc == true)
	{
		close(heredoc_pp[WRITE]);
		heredoc_pp_out = heredoc_pp[READ];
		free(heredoc_pp);
		return (heredoc_pp_out);
	}
	else
	{
		if (heredoc_pp[READ] != 0)
			close(heredoc_pp[READ]);
		if (heredoc_pp[WRITE] != 0)
			close(heredoc_pp[WRITE]);
		free(heredoc_pp);
		return (-1);
	}
}

static void	heredoc_helper(char *line_read, int *heredoc_pp)
{
	char	*line_with_newline;

	line_with_newline = ft_strjoin(line_read, "\n");
	if (line_with_newline == NULL)
		read_heredoc_fail_exit(heredoc_pp);
	write(heredoc_pp[WRITE], line_with_newline,
		ft_strlen(line_with_newline));
	free(line_read);
	free(line_with_newline);
}

static void	reinstate_stdin(int temp_fd)
{
	dup2(temp_fd, STDIN_FILENO);
	close(temp_fd);
}

bool	read_heredoc(int *heredoc_pp,
			t_redir *i_redir, t_exec_block *exec_blocks,
			t_parser_block *parser_blocks)
{
	char	*line_read;
	int		temp_fd;

	temp_fd = dup(STDIN_FILENO);
	signal(SIGINT, signal_handler_heredoc);
	if (pipe(heredoc_pp) == -1)
		redir_creator_fail_exit2(parser_blocks, exec_blocks);
	while (true)
	{
		line_read = readline("\e[1;91m_> \e[46m\e[0m");
		if (line_read == NULL)
		{
			reinstate_stdin(temp_fd);
			read_heredoc_fail_exit(heredoc_pp);
			return (true);
		}
		if (ft_strcmp(line_read, i_redir->id) == 0)
		{
			reinstate_stdin(temp_fd);
			free (line_read);
			return (false);
		}
		heredoc_helper(line_read, heredoc_pp);
	}
}

int	handle_heredocs(t_parser_block *i_parser, t_exec_block *exec_blocks,
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
			if (heredoc_pp[READ] != 0)
			{
				close(heredoc_pp[WRITE]);
				close(heredoc_pp[READ]);
			}
			if (read_heredoc(heredoc_pp, i_redir,
					exec_blocks, parser_blocks) == true)
				return (-2);
		}
		i_redir = i_redir->next;
	}
	return (init_i_exec_with_heredoc(heredoc_pp, i_parser));
}

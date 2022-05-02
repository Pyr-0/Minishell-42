/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:10:31 by shaas             #+#    #+#             */
/*   Updated: 2022/05/01 23:25:43 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	handle_redirs_of_one_block(t_exec_block *i_exec,
					t_parser_block *i_parser, t_exec_block *exec_blocks,
					t_parser_block *parser_blocks)
{
	int		heredoc_fd;
	bool	is_fail;

	is_fail = false;
	heredoc_fd = handle_heredocs(i_exec, i_parser, exec_blocks, parser_blocks);
	is_fail = handle_redir_files(i_exec, i_parser);
	if (heredoc_fd != -1)
		replace_fd(&i_exec->in_fd, heredoc_fd);
	return (is_fail);
}

t_exec_block	*redir_creator(t_parser_block *parser_blocks)
{
	t_exec_block	*exec_blocks;
	t_exec_block	*i_exec;
	t_parser_block	*i_parser;

	exec_blocks = create_exec_blocks(parser_blocks);
	copy_cmd_and_args_to_exec(exec_blocks, parser_blocks);
	i_exec = exec_blocks;
	i_parser = parser_blocks;
	while (i_exec != NULL && i_parser != NULL)
	{
		handle_redirs_of_one_block(i_exec, i_parser,
			exec_blocks, parser_blocks);
		i_exec = i_exec->next;
		i_parser = i_parser->next;
	}
	free_parser_blocks_only_redir(parser_blocks);
	return (exec_blocks);
}

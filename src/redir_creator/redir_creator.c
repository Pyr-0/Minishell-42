/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:10:31 by shaas             #+#    #+#             */
/*   Updated: 2022/04/19 18:31:28 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_pipe(t_exec_block *i_exec, t_exec_block *exec_blocks,
					t_parser_block *parser_blocks)
{
	int	pp[2];
	int	pp_out_dup;
	int	pp_in_dup;

	if (pipe(pp) == -1)
		redir_creator_fail_exit2(parser_blocks, exec_blocks);
	i_exec->pp_out = pp[PIPE_WRITE];
	i_exec->next->pp_in = pp[PIPE_READ];
	pp_in_dup = dup(pp[PIPE_READ]);
	if (pp_in_dup == -1)
		redir_creator_fail_exit2(parser_blocks, exec_blocks);
	replace_fd(&i_exec->next->in_fd, pp_in_dup);
	pp_out_dup = dup(pp[PIPE_WRITE]);
	if (pp_out_dup == -1)
		redir_creator_fail_exit2(parser_blocks, exec_blocks);
	replace_fd(&i_exec->out_fd, pp_out_dup);
}

bool	handle_redirs_of_one_block(t_exec_block *i_exec,
					t_parser_block *i_parser, t_exec_block *exec_blocks,
					t_parser_block *parser_blocks)
{
	int		heredoc_fd;
	bool	is_fail;

	is_fail = false;
	if (i_exec->next != NULL)
		create_pipe(i_exec, exec_blocks, parser_blocks);
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

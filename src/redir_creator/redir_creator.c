/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satori <satori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:10:31 by shaas             #+#    #+#             */
/*   Updated: 2022/04/13 17:52:46 by satori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* void	create_pipe(t_exec_block *i_exec, t_exec_block *exec_blocks,
					t_parser_block *parser_blocks)
{
	int	pp[2];

	if (pipe(pp) == -1)
			redir_creator_fail_exit2(parser_blocks, exec_blocks);
	i_exec->pp_out = pp[PIPE_WRITE];
	i_exec->next->pp_in = pp[PIPE_READ];
}

bool	handle_redirs_of_one_block(t_exec_block *i_exec,
					t_parser_block *i_parser, t_exec_block *exec_blocks,
					t_parser_block *parser_blocks)
{
	t_redir	*i_redir;
	
	if (i_exec->next != NULL)
		create_pipe(i_exec, exec_blocks, parser_blocks);
	i_redir = parser_blocks->output;
	while (i_redir != NULL)
	{
		if (open_output_file(i_redir, exec_blocks, parser_blocks) == true)
			return (true);
		i_redir = i_redir->next;
	}
	i_redir = parser_blocks->input;
	while (i_redir != NULL)
	{
		if (i_redir->e_redir_type != REDIR_INPUT_HEREDOC)
		{
			if (open_input_file(i_redir, exec_blocks, parser_blocks) == true)
				return (true);
		}
		i_redir = i_redir->next;
	}
	return (false);
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
		if (handle_redirs_of_one_block(i_exec, i_parser,
				exec_blocks, parser_blocks) == true)
			return (NULL);
		i_exec = i_exec->next;
		i_parser = i_parser->next;
	}
	free_parser_blocks_only_redir(parser_blocks);
	return (exec_blocks);
}
 */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:10:31 by shaas             #+#    #+#             */
/*   Updated: 2022/04/14 00:59:38 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replace_fd(int *old_fd, int new_fd)
{
	if (*old_fd > STDERR_FILENO)
		close (*old_fd);
	*old_fd = new_fd;
}

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
	pp_out_dup = dup(pp[PIPE_WRITE]);
	if (pp_out_dup == -1)
		redir_creator_fail_exit2(parser_blocks, exec_blocks);
	replace_fd(&i_exec->out_fd, pp_out_dup);
	pp_in_dup = dup(pp[PIPE_READ]);
	if (pp_in_dup == -1)
		redir_creator_fail_exit2(parser_blocks, exec_blocks);
	replace_fd(&i_exec->next->in_fd, pp_in_dup);
}

bool	open_output_file(t_redir *output, t_exec_block *curr)
{
	int	fd;

	if (access(output->id, F_OK) != 0)
	{
		if (output->e_redir_type == REDIR_OUTPUT_APPEND)
			fd = open(output->id, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (output->e_redir_type == REDIR_OUTPUT_REPLACE)
			fd = open(output->id, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else if (access(output->id, W_OK) != 0)
		return (redir_creator_handle_error(output->id, "Darlin', you don't have permissions to write to this file"));
	else
	{
		if (output->e_redir_type == REDIR_OUTPUT_APPEND)
			fd = open(output->id, O_WRONLY | O_APPEND);
		else if (output->e_redir_type == REDIR_OUTPUT_REPLACE)
			fd = open(output->id, O_WRONLY | O_TRUNC);
	}
	if (fd == -1)
		return (redir_creator_handle_error(output->id, "the file doesn't wanna open sorry"));
	replace_fd(&curr->out_fd, fd);
	return (false);
}

bool	open_input_file(t_redir *input, t_exec_block *curr)
{
	int	fd;

	if (access(input->id, F_OK) != 0)
		return (redir_creator_handle_error(input->id, "Gurl that file doesn't exist"));
	else if (access(input->id, R_OK) != 0)
		return (redir_creator_handle_error(input->id, "Darlin', you don't have permissions to read from this file"));
	else
		fd = open(input->id, O_RDONLY);
	if (fd == -1)
		return (redir_creator_handle_error(input->id, "the file doesn't wanna open sorry"));
	replace_fd(&curr->in_fd, fd);
	return (false);
}

bool	redir_handler_fail(t_exec_block *i_exec)
{
	free(i_exec->cmd);
	i_exec->cmd = NULL;
	return (true);
}

bool	handle_redirs_of_one_block(t_exec_block *i_exec,
					t_parser_block *i_parser, t_exec_block *exec_blocks,
					t_parser_block *parser_blocks)
{
	t_redir	*i_redir;

	if (i_exec->next != NULL)
		create_pipe(i_exec, exec_blocks, parser_blocks);
	i_redir = i_parser->input;
	while (i_redir != NULL)
	{
		if (i_redir->e_redir_type != REDIR_INPUT_HEREDOC)
		{
			if (open_input_file(i_redir, i_exec) == true)
				return (redir_handler_fail(i_exec));
		}
		i_redir = i_redir->next;
	}
	i_redir = i_parser->output;
	while (i_redir != NULL)
	{
		if (open_output_file(i_redir, i_exec) == true)
			return (redir_handler_fail(i_exec));
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
		handle_redirs_of_one_block(i_exec, i_parser,
				exec_blocks, parser_blocks);
		i_exec = i_exec->next;
		i_parser = i_parser->next;
	}
	free_parser_blocks_only_redir(parser_blocks);
	return (exec_blocks);
}

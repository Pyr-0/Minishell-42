/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_files.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:31:04 by shaas             #+#    #+#             */
/*   Updated: 2022/04/19 19:15:00 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	open_output_file(t_redir *output, t_exec_block *curr)
{
	int	fd;

	fd = -1;
	if (access(output->id, F_OK) != 0)
	{
		if (output->e_redir_type == REDIR_OUTPUT_APPEND)
			fd = open(output->id, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (output->e_redir_type == REDIR_OUTPUT_REPLACE)
			fd = open(output->id, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else if (access(output->id, W_OK) != 0)
		return (redir_creator_handle_error(output->id,
				"Darlin', you don't have permissions to write to this file"));
	else
	{
		if (output->e_redir_type == REDIR_OUTPUT_APPEND)
			fd = open(output->id, O_WRONLY | O_APPEND);
		else if (output->e_redir_type == REDIR_OUTPUT_REPLACE)
			fd = open(output->id, O_WRONLY | O_TRUNC);
	}
	if (fd == -1)
		return (redir_creator_handle_error(output->id,
				"the file doesn't wanna open sorry"));
	replace_fd(&curr->out_fd, fd);
	return (false);
}

bool	open_input_file(t_redir *input, t_exec_block *curr)
{
	int	fd;

	if (access(input->id, F_OK) != 0)
		return (redir_creator_handle_error(input->id,
				"Gurl that file doesn't exist"));
	else if (access(input->id, R_OK) != 0)
		return (redir_creator_handle_error(input->id,
				"Darlin', you don't have permissions to read from this file"));
	else
		fd = open(input->id, O_RDONLY);
	if (fd == -1)
		return (redir_creator_handle_error(input->id,
				"the file doesn't wanna open sorry"));
	replace_fd(&curr->in_fd, fd);
	return (false);
}

bool	handle_redir_files(t_exec_block *i_exec, t_parser_block *i_parser)
{
	t_redir	*i_redir;

	i_redir = i_parser->redir;
	while (i_redir != NULL)
	{
		if (i_redir->e_redir_type == REDIR_INPUT_FILE)
		{
			if (open_input_file(i_redir, i_exec) == true)
				return (redir_handler_fail(i_exec));
		}
		if (i_redir->e_redir_type == REDIR_OUTPUT_REPLACE
			|| i_redir->e_redir_type == REDIR_OUTPUT_APPEND)
		{
			if (open_output_file(i_redir, i_exec) == true)
				return (redir_handler_fail(i_exec));
		}
		i_redir = i_redir->next;
	}
	return (false);
}

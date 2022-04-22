/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_files.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:31:04 by shaas             #+#    #+#             */
/*   Updated: 2022/04/22 13:20:53 by mrojas-e         ###   ########.fr       */
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
		return (redir_creator_handle_error(output->id, "\e[31mDarlin', \
you don't have permissions to write to this file 👀\e[0m"));
	else
	{
		if (output->e_redir_type == REDIR_OUTPUT_APPEND)
			fd = open(output->id, O_WRONLY | O_APPEND);
		else if (output->e_redir_type == REDIR_OUTPUT_REPLACE)
			fd = open(output->id, O_WRONLY | O_TRUNC);
	}
	if (fd == -1)
		return (redir_creator_handle_error(output->id,
				"\e[31mthe file doesn't wanna open sorry 🤷‍♀️\e[0m"));
	replace_fd(&curr->out_fd, fd);
	return (false);
}

bool	open_input_file(t_redir *input, t_exec_block *curr)
{
	int	fd;

	if (access(input->id, F_OK) != 0)
		return (redir_creator_handle_error(input->id,
				"\e[31mDarlin', that file doesn't exist 🙅‍♀️\e[0m"));
	else if (access(input->id, R_OK) != 0)
		return (redir_creator_handle_error(input->id, "\e[31mDarlin', \
you don't have permissions to write to this file 👀\e[0m"));
	else
		fd = open(input->id, O_RDONLY);
	if (fd == -1)
		return (redir_creator_handle_error(input->id,
				"\e[31mthe file doesn't wanna open sorry 🤷‍♀️\e[0m"));
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

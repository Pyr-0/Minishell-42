/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:10:31 by shaas             #+#    #+#             */
/*   Updated: 2022/04/18 12:48:10 by shaas            ###   ########.fr       */
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
		line_read = readline("heredoc> "); // ft_strdup("hello echo me"); // readline("mi[SHELL]in$ ");
		if (line_read == NULL)
			read_heredoc_fail_exit(heredoc_pp, parser_blocks, exec_blocks);
		if (ft_strcmp(line_read, i_redir->id) == 0)
		{
			free (line_read);
			return ;
		}
		line_with_newline = ft_strjoin(line_read, "\n");
		if (line_with_newline == NULL)
			read_heredoc_fail_exit(heredoc_pp, parser_blocks, exec_blocks);
		write(heredoc_pp[PIPE_WRITE], line_with_newline, ft_strlen(line_with_newline));
		free(line_read);
		free(line_with_newline);
	}
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

int	init_i_exec_with_heredoc(int *heredoc_pp, t_exec_block *i_exec, t_parser_block *i_parser)
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
		if (i_redir->e_redir_type == REDIR_OUTPUT_REPLACE || i_redir->e_redir_type == REDIR_OUTPUT_APPEND)
		{
			if (open_output_file(i_redir, i_exec) == true)
				return (redir_handler_fail(i_exec));
		}
		i_redir = i_redir->next;
	}
	return (false);
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

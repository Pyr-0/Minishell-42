/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:10:31 by shaas             #+#    #+#             */
/*   Updated: 2022/03/31 19:57:58 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_exec_block	*redir_creator(t_parser_block *parser_blocks)
{
	t_parser_block	*first_parser;
	t_exec_block	*exec_blocks;
	t_exec_block	*first_exec;

	first_parser = parser_blocks;
	exec_blocks = init_exec_blocks(parser_blocks, first_parser);
	first_exec = exec_blocks;
	while (parser_blocks != NULL)
	{
		if (first_parser != parser_blocks)
			add_exec_block()
		if (parser_blocks->next != NULL)
			redir_creator_create_pipe(exec_blocks, )
	}
}

t_exec_block	*init_exec_block(t_parser_block *parser_blocks, t_exec_block *first)
{
	t_exec_block	*exec_block;

	exec_block = malloc(sizeof(t_exec_block));
	if (exec_block == NULL)
		redir_creator_fail_exit(parser_blocks, first);
	exec_block->cmd = NULL;
	exec_block->arg = NULL;
	exec_block->in_fd = STDIN_FILENO;
	exec_block->out_fd = STDOUT_FILENO;
	exec_block->next = NULL;
	return (exec_block);
}

t_exec_block	*add_exec_block(t_exec_block *prev, t_exec_block *first, t_parser_block *parser_blocks)
{
	t_exec_block *new;

	new = init_exec_block(parser_blocks, first);
	if (prev != NULL)
		prev->next = new;
	return (new);
}

void	copy_args_per_node(t_exec_block *i_exec, t_parser_block *i_parser, t_exec_block *first_exec, t_parser_block *first_parser)
{
	t_arg	*i_arg_parser;
	t_arg	*i_arg_exec;

	i_arg_parser = i_parser->arg;
	i_arg_exec = i_exec->arg;
	while (i_arg_parser != NULL)
	{
		
	}
}

void	copy_args_from_parser_to_exec(t_exec_block *first_exec, t_parser_block *first_parser)
{
	t_parser_block	*i_parser;
	t_exec_block	*i_exec;

	i_exec = first_exec;
	i_parser = first_parser;
	while (i_parser != NULL && i_exec != NULL)
	{
		i_exec->cmd = ft_strdup(i_parser->cmd);
		if (i_exec->cmd = NULL)
			redir_creator_fail_exit(first_parser, first_exec);
		copy_args_per_node(i_exec, i_parser, first_exec, first_parser);
		
	}
}

t_exec_block	*init_exec_blocks(t_parser_block *parser_blocks)
{
	t_exec_block	*exec_blocks;
	t_exec_block	*first_exec;
	int				block_num;
	int				i;

	i = 1;
	block_num = get_parser_block_num(parser_blocks);
	exec_blocks = init_exec_block(parser_blocks, NULL);
	first_exec = exec_blocks;
	while (i < block_num)
	{
		exec_blocks = add_exec_block(exec_blocks, first_exec, parser_blocks);
		i++;
	}
	copy_args_from_parser_to_exec(first_exec, parser_blocks);
	return (first_exec);
}

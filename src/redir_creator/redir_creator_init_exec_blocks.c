/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_creator_init_exec_blocks.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 20:09:21 by shaas             #+#    #+#             */
/*   Updated: 2022/05/02 17:43:16 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_exec_block	*init_exec_block(t_parser_block *parser_blocks,
	t_exec_block *first)
{
	t_exec_block	*new;

	new = malloc(sizeof(t_exec_block));
	if (new == NULL)
		redir_creator_fail_exit1(parser_blocks, first);
	new->cmd = NULL;
	new->arg = NULL;
	new->in_fd = STDIN_FILENO;
	new->out_fd = STDOUT_FILENO;
	new->next = NULL;
	return (new);
}

t_exec_block	*add_exec_block(t_exec_block *first, t_exec_block *prev,
		t_parser_block *parser_blocks)
{
	t_exec_block	*new;

	new = init_exec_block(parser_blocks, first);
	if (prev != NULL)
		prev->next = new;
	return (new);
}

void	copy_cmd_and_args_to_exec(t_exec_block *first_exec,
	t_parser_block *first_parser)
{
	t_parser_block	*i_parser;
	t_exec_block	*i_exec;

	i_exec = first_exec;
	i_parser = first_parser;
	while (i_parser != NULL && i_exec != NULL)
	{
		i_exec->cmd = i_parser->cmd;
		i_exec->arg = i_parser->arg;
		i_parser = i_parser->next;
		i_exec = i_exec->next;
	}
}

t_exec_block	*create_exec_blocks(t_parser_block *parser_blocks)
{
	int				parser_block_count;
	int				i;
	t_exec_block	*temp_block;
	t_exec_block	*first;

	i = 0;
	first = NULL;
	temp_block = first;
	parser_block_count = get_parser_block_num(parser_blocks);
	while (i < parser_block_count)
	{
		temp_block = add_exec_block(first, temp_block, parser_blocks);
		if (first == NULL)
			first = temp_block;
		i++;
	}
	return (first);
}
